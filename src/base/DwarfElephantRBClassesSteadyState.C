/**
 * In this class subclasses of the RBEvaluation and
 * RBConstruction class are introduced.
 *
 * DwarfElephantRBEvaluation: requires only the definition of the lower
 * coercivity constant. The value is here specified for a three layer
 * problem.
 *
 * DwarfElephantRBConstruction: In order to construct the RB System with the
 * DwarfElephantRBEvaluation subclass the method build_rb_evaluation needs to be
 * overriden.
 *
 * NOTE: ENSURE THAT THE CLASS IS USING THE CORRECT RBSTRUCTURES.
 */

// First commit of branch
 ///-------------------------------------------------------------------------
 #include "DwarfElephantRBClassesSteadyState.h"
#include "libmesh/timestamp.h"


DwarfElephantRBConstructionSteadyState::DwarfElephantRBConstructionSteadyState (EquationSystems & es,
                                                                                const std::string & name_in,
                                                                                const unsigned int number_in)
    : Parent(es, name_in, number_in)
  { }

void
DwarfElephantRBConstructionSteadyState::init_data()
{
  u_var = this->add_variable(get_equation_systems().get_system(0).variable_name(0) + "(RB)");
  Parent::init_data();
}

 
DwarfElephantRBEvaluationSteadyState::DwarfElephantRBEvaluationSteadyState(const libMesh::Parallel::Communicator & comm, FEProblemBase & fe_problem, bool _RB_RFA_in):
    RBEvaluation(comm),
    fe_problem(fe_problem),
        _RB_RFA(_RB_RFA_in)
{
  //set_rb_theta_expansion(_eim_test_rb_theta_expansion);
  //set_rb_theta_expansion(_goem_2D_rb_theta_expansion);
  set_rb_theta_expansion(RBExpansion);
  //set_rb_theta_expansion(_geom_3D_rb_theta_expansion);
}

Real
DwarfElephantRBEvaluationSteadyState::get_stability_lower_bound()
{
  /*
  const RBParameters & mu = get_parameters();

  Real min_mu = mu.get_value("mu_0");

  for (unsigned int  i = 1; i != mu.n_parameters(); i++)
  {
    const std::string mu_name = "mu_" + std::to_string(i);
    Real min_mu_i = std::min(min_mu, mu.get_value(mu_name));

    if (min_mu_i < min_mu)
      min_mu = min_mu_i;
  }

  return min_mu; */
  // rb_scm_eval->set_parameters(get_parameters());
  // return rb_scm_eval->get_SCM_LB();
  return 0.0237;
}

DwarfElephantEIMEvaluationSteadyState::DwarfElephantEIMEvaluationSteadyState(const libMesh::Parallel::Communicator & comm) :
    RBEIMEvaluation(comm)
  {
    attach_parametrized_function(&sg);
  }

  /**
   * Constructor.
   */
  DwarfElephantEIMConstructionSteadyState::DwarfElephantEIMConstructionSteadyState (EquationSystems & es,
                         const std::string & name_in,
                         const unsigned int number_in)
    : Parent(es, name_in, number_in)
  {
  }

  void DwarfElephantEIMConstructionSteadyState::init_data()
  {
    Parent::init_data();
  }
  
  std::unique_ptr<ElemAssembly> DwarfElephantEIMConstructionSteadyState::build_eim_assembly(unsigned int index)
  {
    DwarfElephantEIMConstructionSteadyState::_rb_eim_assembly_objects_new.push_back(libmesh_make_unique<DwarfElephantEIMFAssembly>(*this, index));
    return libmesh_make_unique<DwarfElephantEIMFAssembly>(*this, index);
  }
  /**
   * Initialize the implicit system that is used to perform L2 projections.
   */
  void DwarfElephantEIMConstructionSteadyState::init_implicit_system()
  {
    this->add_variable ("L2_proj_var"); // variable name should be the same as the one defined in the MOOSE input file for compatibility with EIM
  }

  /**
   * Initialize the explicit system that is used to store the basis functions.
   */
  void DwarfElephantEIMConstructionSteadyState::init_explicit_system()
  {
    u_var = get_explicit_system().add_variable ("f_EIM");//, libMesh::FIRST);
  }
