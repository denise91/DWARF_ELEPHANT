#include "Predictor.h"

#include "DwarfElephantSystem.h"
#include "DwarfElephantRBProblem.h"

DwarfElephantSystem::DwarfElephantSystem(FEProblemBase & _fe_problem, const std::string & name) :
    NonlinearSystem(_fe_problem, name)
{
}

DwarfElephantSystem::~DwarfElephantSystem()
{
}

// void
// DwarfElephantSystem::initialSetup()
// {
//   // Initialize the solution vector
// }

void
DwarfElephantSystem::solve()
{
  NumericVector<Number> * _current_rb_solution;

  _current_rb_solution = _sys.current_local_solution.get();
  _current_rb_solution->zero();


  if (_fe_problem.solverParams()._type != Moose::ST_LINEAR)
  {
    // set the boundaries for the FEM solutions
    _computing_initial_residual = true;

    // In case your are using a MOOSE version older than April 19th 2018 uncomment the following line
    // _fe_problem.computeResidual(_transient_sys, *_current_solution, *_transient_sys.rhs);
    _fe_problem.computeResidualSys(_nl_implicit_sys, *_current_rb_solution, *_nl_implicit_sys.rhs);
    // _fe_problem.computeResidualSys(_transient_sys, *_current_rb_solution, *_transient_sys.rhs);

    _computing_initial_residual = false;
    // _transient_sys.rhs->close();
    _nl_implicit_sys.rhs->close();

    // _initial_residual_before_preset_bcs = _transient_sys.rhs->l2_norm();
    _initial_residual_before_preset_bcs = _nl_implicit_sys.rhs->l2_norm();
    if (_compute_initial_residual_before_preset_bcs)
      _console << "Initial residual before setting preset BCs: "
               << _initial_residual_before_preset_bcs << '\n';
  }

  // set the counters for the iterations to zero
  _current_l_its.clear();
  _current_nl_its = 0;

  // Initialize the solution vector
  DwarfElephantRBProblem * _rb_problem = cast_ptr<DwarfElephantRBProblem *>(&_fe_problem);
  if(_rb_problem->getUseReducedInitialCondition())
    _rb_problem->setReducedInitialCondition();
  else
    setInitialSolution();

  if(_use_finite_differenced_preconditioner)
    setupFiniteDifferencedPreconditioner();

//  system().solve();

// calculate the stiffness matrices
// In case your are using a MOOSE version older than April 19th 2018 uncomment the following line
// _fe_problem.computeJacobian(_transient_sys, *_current_solution, *_transient_sys.matrix);
  // _fe_problem.computeJacobianSys(_transient_sys, *_current_rb_solution, *_transient_sys.matrix);
  _fe_problem.computeJacobianSys(_nl_implicit_sys, *_current_rb_solution, *_nl_implicit_sys.matrix);

//  DwarfElephantRBProblem & _rb_problem = cast_ref<DwarfElephantRBProblem &>(_fe_problem);

//  std::vector<std::string> _kernel_names = _rb_problem.getKernelNames();

//  for(unsigned int i = 0; i < _kernel_names.size(); i++)
//  {
//    std::shared_ptr<DwarfElephantRBKernel> _rb_kernel_ptr = std::static_pointer_cast<DwarfElephantRBKernel> (_kernels.getActiveObject(_kernel_names[i]));
//    _console << _kernel_names[i] << std::endl;
//    _rb_kernel_ptr->computeOutput();
//  }
}
