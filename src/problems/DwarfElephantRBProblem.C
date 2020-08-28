 ///-------------------------------------------------------------------------
// MOOSE includes (DwarfElephant package)
#include "DwarfElephantRBProblem.h"

#include "Assembly.h"
#include "AuxiliarySystem.h"
#include "MooseEigenSystem.h"
#include "NonlinearSystem.h"

template<>
InputParameters validParams<DwarfElephantRBProblem>()
{
  InputParameters params = validParams<FEProblemBase>();

  return params;
}

DwarfElephantRBProblem::DwarfElephantRBProblem(const InputParameters & params):
  FEProblemBase(params),
  _nl_sys(std::make_shared<DwarfElephantSystem>(*this, "rb0"))

{
    _nl = _nl_sys;
    _aux = std::make_shared<AuxiliarySystem>(*this, "aux0");

    //_assembly = _rb_assembly;

    newRBAssemblyArray(*_nl_sys); // Edited code 6.8.2018

    newAssemblyArray(*_nl_sys);
//    initNullSpaceVectors(parameters, *_nl_sys);

    _eq.parameters.set<DwarfElephantRBProblem *>("_fe_problem") = this;
}

DwarfElephantRBProblem::~DwarfElephantRBProblem()
{
  //FEProblemBase::deleteAssemblyArray();
}

void
DwarfElephantRBProblem::init()
{
  if (_initialized)
    return;

  unsigned int n_vars = _nl->nVariables();
  switch (_coupling)
  {
    case Moose::COUPLING_DIAG:
      _cm = libmesh_make_unique<CouplingMatrix>(n_vars);
      for (unsigned int i = 0; i < n_vars; i++)
        for (unsigned int j = 0; j < n_vars; j++)
          (*_cm)(i, j) = (i == j ? 1 : 0);
      break;

    // for full jacobian
    case Moose::COUPLING_FULL:
      _cm = libmesh_make_unique<CouplingMatrix>(n_vars);
      for (unsigned int i = 0; i < n_vars; i++)
        for (unsigned int j = 0; j < n_vars; j++)
          (*_cm)(i, j) = 1;
      break;

    case Moose::COUPLING_CUSTOM:
      // do nothing, _cm was already set through couplingMatrix() call
      break;
  }

  _nl->dofMap()._dof_coupling = _cm.get();
  _nl->dofMap().attach_extra_sparsity_function(&extraSparsity, _nl.get());
  _nl->dofMap().attach_extra_send_list_function(&extraSendList, _nl.get());
  _aux->dofMap().attach_extra_send_list_function(&extraSendList, _aux.get());

  if (_solve && n_vars == 0)
    mooseError("No variables specified in the FEProblemBase '", name(), "'.");

  ghostGhostedBoundaries(); // We do this again right here in case new boundaries have been added

  // do not assemble system matrix for JFNK solve
  if (solverParams()._type == Moose::ST_JFNK)
    _nl->turnOffJacobian();

  Moose::perf_log.push("eq.init()", "Setup");
  //std::cout << "Calling _eq.init()" << std::endl;
  _eq.init();
  //std::cout << "Done calling _eq.init()" << std::endl;
  Moose::perf_log.pop("eq.init()", "Setup");

  Moose::perf_log.push("FEProblemBase::init::meshChanged()", "Setup");
  _mesh.meshChanged();
  if (_displaced_problem)
    _displaced_mesh->meshChanged();
  Moose::perf_log.pop("FEProblemBase::init::meshChanged()", "Setup");

  Moose::perf_log.push("NonlinearSystem::update()", "Setup");
  _nl->update();
  Moose::perf_log.pop("NonlinearSystem::update()", "Setup");

  for (THREAD_ID tid = 0; tid < libMesh::n_threads(); ++tid)
    _assembly[tid]->init(_cm.get());

  _nl->init();

  if (_displaced_problem)
    _displaced_problem->init();

  _aux->init();

  _initialized = true;
}


void
DwarfElephantRBProblem::setInputParametersFEProblem(InputParameters & parameters)
{
  // set _fe_problem
  FEProblemBase::setInputParametersFEProblem(parameters);
  // set _fe_problem
  // parameters.set<DwarfElephantRBProblem *>("_fe_problem") = this;
}

void
DwarfElephantRBProblem::solve()
{
  Moose::perf_log.push("constructRB()", "Execution");

#ifdef LIBMESH_HAVE_PETSC
  Moose::PetscSupport::petscSetOptions(*this); // Make sure the PETSc options are setup for this app
#endif

  if (_solve)
    _nl_sys->solve();

  if (_solve)
    _nl_sys->update();

  Moose::perf_log.pop("constructRB()", "Execution");
}

void
DwarfElephantRBProblem::newRBAssemblyArray(NonlinearSystemBase & nl)
{
  unsigned int subdomains = mesh().meshSubdomains().size();
  unsigned int boundaries = mesh().meshBoundaryIds().size();
  unsigned int size = 0;

  if (subdomains > boundaries)
    size = subdomains;
  else
    size = boundaries;

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
