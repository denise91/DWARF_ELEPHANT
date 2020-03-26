 ///-------------------------------------------------------------------------
// MOOSE includes (DwarfElephant package)
#include "DwarfElephantRBProblem.h"

#include "Assembly.h"
#include "AuxiliarySystem.h"
#include "MooseEigenSystem.h"
#include "NonlinearSystem.h"

registerMooseObject("DwarfElephantApp", DwarfElephantRBProblem);

template<>
InputParameters validParams<DwarfElephantRBProblem>()
{
  InputParameters params = validParams<FEProblemBase>();
  params.addParam<bool>("use_reduced_initial_condition", false, "Enable/disable the use of the a reduced initial condition.");
  params.addParam<bool>("user_defined_assembly_size", false, "User defines the size of RBAssembly.");
  params.addParam<unsigned int>("assembly_size", 0 ,"Size of RBAssembly.");
  params.addParam<UserObjectName>("initial_rb_userobject","initializeRBSystem","Name of the UserObject for initializing the RB system.");
  params.addParam<UserObjectName>("offline_online_rb_userobject", "performRBSystem" ,"Name of the UserObject for the offline/online stage.");
  params.addParam<std::string>("file", "Name and path of the data file, valid delimiter is new line.");
  params.addParam<std::string>("offline_data_name","offline_data","Folder where the offline data should be stored.");
  return params;
}

DwarfElephantRBProblem::DwarfElephantRBProblem(const InputParameters & params):
  FEProblemBase(params),
  _initial_rb_userobject(getParam<UserObjectName>("initial_rb_userobject")),
  _offline_online_rb_userobject(getParam<UserObjectName>("offline_online_rb_userobject")),
  _nl_sys(std::make_shared<DwarfElephantSystem>(*this, "rb0")),
  _use_reduced_initial_condition(getParam<bool>("use_reduced_initial_condition")),
  _user_defined_assembly_size(getParam<bool>("user_defined_assembly_size")),
  _assembly_size(getParam<unsigned int>("assembly_size")),
  _offline_data_name(getParam<std::string>("offline_data_name"))
{
    _nl = _nl_sys;
    _aux = std::make_shared<AuxiliarySystem>(*this, "aux0");

    //_assembly = _rb_assembly;

    newRBAssemblyArray(*_nl_sys);

    newAssemblyArray(*_nl_sys);
//    initNullSpaceVectors(parameters, *_nl_sys);

    _eq.parameters.set<DwarfElephantRBProblem *>("_fe_problem") = this;
}

DwarfElephantRBProblem::~DwarfElephantRBProblem()
{
  // FEProblemBase::deleteAssemblyArray();
}

void
DwarfElephantRBProblem::setInputParametersFEProblem(InputParameters & parameters)
{
  // set _fe_problem
  FEProblemBase::setInputParametersFEProblem(parameters);
  // set _fe_problem
  // parameters.set<DwarfElephantRBProblem *>("_dwarf_fe_problem") = this;
}

void
DwarfElephantRBProblem::solve()
{
  // Moose::perf_log.push("constructRB()", "Execution");

#ifdef LIBMESH_HAVE_PETSC
  Moose::PetscSupport::petscSetOptions(*this); // Make sure the PETSc options are setup for this app
#endif

  if (_solve)
    _nl_sys->solve();

  if (_solve)
    _nl_sys->update();

  // Moose::perf_log.pop("constructRB()", "Execution");
}

void
DwarfElephantRBProblem::newRBAssemblyArray(NonlinearSystemBase & nl)
{
  unsigned int subdomains = mesh().meshSubdomains().size();
  unsigned int boundaries = mesh().meshBoundaryIds().size();
  unsigned int size = 0;

  if(_user_defined_assembly_size)
    size = _assembly_size;
  else
  {
    if (subdomains > boundaries)
      size = subdomains;
    else
      size = boundaries;
  }

  _rb_assembly.resize(size);

  for (unsigned int i = 0; i < size; i++)
    _rb_assembly[i] = new DwarfElephantRBAssembly(nl, i);
}

// MooseVariable &
// DwarfElephantRBProblem::getVariable(THREAD_ID tid, const std::string & var_name)
// {
//   if (_nl->hasVariable(var_name))
//     return _nl->getVariable(tid, var_name);
//   else if (!_aux->hasVariable(var_name))
//     mooseError("Unknown variable " + var_name);
//
//   return _aux->getVariable(tid, var_name);
// }

void
DwarfElephantRBProblem::setReducedInitialCondition()
{
  // Get reference and pointer to RBEvaluation and RBConstruction
  // Read the offline data for retrieving the basis functions
  DwarfElephantRBEvaluationTransient _rb_eval(comm() , *this);

  const DwarfElephantInitializeRBSystemTransient & _initialize_rb_system =
    getUserObject<DwarfElephantInitializeRBSystemTransient>(_initial_rb_userobject);

  _initialize_rb_system.get_rb_con_ptr()->set_rb_evaluation(_rb_eval);

  #if defined(LIBMESH_HAVE_CAPNPROTO)
    RBDataDeserialization::TransientRBEvaluationDeserialization _rb_eval_reader(_rb_eval);
    _rb_eval_reader.read_from_file("trans_rb_eval.bin", /*read_error_bound_data*/ true);
  #else
    _rb_eval.legacy_read_offline_data_from_files(_offline_data_name, true);
  #endif

  _rb_eval.read_in_basis_functions(*_initialize_rb_system.get_rb_con_ptr(), _offline_data_name, true);

  // Read the reduced state from file and set it as RB_solution
  _file = getParam<std::string>("file");
  fileParser(_rb_eval);

  // project the reduced state back to the full state
  _initialize_rb_system.get_rb_con_ptr()->solution->zero();

  if (_rb_eval.RB_solution.size() > _rb_eval.get_n_basis_functions())
    mooseError("RB_solution in DwarfElephantRBProblem is too long!");

  for (auto i : IntRange<unsigned int>(0, _rb_eval.RB_solution.size()))
    _initialize_rb_system.get_rb_con_ptr()->solution->add(_rb_eval.RB_solution(i), _rb_eval.get_basis_function(i));

  *_eq.get_system("rb0").solution = *_eq.get_system("RBSystem").solution;
  this->getNonlinearSystemBase().update();
  // ExodusII_IO(mesh()).write_equation_systems ("initial_condition.e", es());
  // _eq.get_system("rb0").solution->zero();
  // this->getNonlinearSystemBase().update();
}

void
DwarfElephantRBProblem::fileParser(DwarfElephantRBEvaluationTransient & _rb_eval)
{
  // define all necessary parameters
  std::string _line;

  // Check inputFile and create input stream.
  MooseUtils::checkFileReadable(_file);
  std::ifstream _input_file;

  // Open the inputFile and check it.
  _input_file.open(_file.c_str());
  if (!_input_file.good())
    mooseError("Error while opening the file '", _file, "' within the DwarfElephantFileReader function.");

  // Read the file.
  std::vector<Real> _all_data;
  while (std::getline(_input_file, _line))
  {
    if (_line[0] != '#')
    {
      // Parse the data to the corresponding vectors
      std::istringstream _iss(_line);
      Real _data_value;
      while (_iss >> _data_value)
        _all_data.push_back(_data_value);
    }
  }
  _input_file.close();
  _rb_eval.RB_solution = _all_data;
}
