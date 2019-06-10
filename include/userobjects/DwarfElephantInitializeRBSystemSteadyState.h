/* This UserObject is required to initialitze the RB system structure
 * and transfer for the steady state case.
 */

///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTINITIALIZERBSYSTEMSTEADYSTATE_H
#define DWARFELEPHANTINITIALIZERBSYSTEMSTEADYSTATE_H

///---------------------------------INCLUDES--------------------------------
//libMesh includes
#include "libmesh/equation_systems.h"
#include "libmesh/sparse_matrix.h"
#include "libmesh/petsc_matrix.h"
#include "libmesh/petsc_vector.h"


// MOOSE includes
#include "GeneralUserObject.h"
#include "DisplacedProblem.h"
#include "MooseMesh.h"
#include "MooseVariable.h"

// MOOSE includes (DwarfElephant package)
#include "DwarfElephantSystem.h"
#include "DwarfElephantRBClassesSteadyState.h"
#include <boost/lexical_cast.hpp>
#include<sstream>
///-------------------------------------------------------------------------
// Forward Declarations
namespace libMesh
{
  class EquationSystems;
  template <typename T> class SparseMatrix;
  template <typename T> class PetscMatrix;
  template <typename T> class PetscVector;
  
  class RBSCMEvaluation;
  class RBSCMConstruction;
}

class MooseMesh;
class DwarfElephantSystem;
class DwarfElephantRBKernel;
class DwarfElephantRBConstructionSteadyState;
class DwarfElephantRBEvaluationSteadyState;
class DwarfElephantEIMConstructionSteadyState;
class DwarfElephantEIMEvaluationSteadyState;
class DwarfElephantInitializeRBSystemSteadyState;
class DwarfElephantEIMFKernel;
class DwarfElephantEIMAKernel;
class DwarfElephantEIMFKernelsAction;
class DwarfElephantComputeEIMInnerProductMatrixSteadyState;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantInitializeRBSystemSteadyState>();

///-------------------------------------------------------------------------
class DwarfElephantInitializeRBSystemSteadyState :
  public GeneralUserObject
{

//----------------------------------PUBLIC----------------------------------
  public: // To do: Add RB parameters to this class
    DwarfElephantInitializeRBSystemSteadyState(const InputParameters & params);
    DwarfElephantInitializeRBSystemSteadyState & operator=(const DwarfElephantInitializeRBSystemSteadyState &);
    /* Methods */
    ~DwarfElephantInitializeRBSystemSteadyState()
    {
      // Delete statements added to prevent memory leaks
      if (_use_EIM) { delete _eim_eval_ptr;}
      delete _rb_eval_ptr;
      if (_use_hp_EIM && _offline_stage) { delete _hp_eim_tree_ptr;}
      if (_use_hp_EIM && !_offline_stage) { delete _online_hp_eim_tree_ptr;}
    }
    // Initializes all required matrices and vectors for the RB solve.
    void initializeOfflineStage();
    void initializeOfflineStageEIM();
    void initializeOfflineStage_hp_EIM();
    void initializeOfflineStageRBOnly();
    
    void processEIMParameters();
    void processRBParameters() const;
    //void processSCMParameters();
    void initializeEIM();
    void initializeRBOnly();
    void AssignAffineMatricesAndVectors() const;

    // Initializes the RB System.
    virtual void initialize() override;

    // Method not used in this UserObject.
    virtual void execute() override;

    // Method not used in this UserObject.
    virtual void finalize() override;
    
    void initializehpEIMTesting();
    
    void initializehpEIMOnline();
    
    void read_and_create_hpEIM_tree(EquationSystems & _es, MooseMesh * _mesh_ptr, EIM_input_data _eim_data_in, std::string filename, DwarfElephanthpEIMM_aryTree* & tree)
    // Reads file with given name to construct hp EIM tree based on the information therein
    // The "_online_hp_eim_tree_ptr" member of this class points to the tree object that this function creates
    {
        std::ifstream input_file;
        bool children_exist;
        int number_of_params;
        double EIM_error, RB_error_bound;
        std::vector<Real> param_min, param_max;
        input_file.open(filename);
        if (input_file.fail()) {    mooseError("Tree file provided does not exist.");}
    
        std::vector<Real> temp_vec;
        std::string word_in;
        std::getline(input_file,word_in,','); // read child_exist flag
        std::istringstream(word_in) >> children_exist;
        //children_exist = boost::lexical_cast<bool>(word_in);
        std::getline(input_file,word_in,',');
        std::istringstream(word_in) >> number_of_params;
        //number_of_params = boost::lexical_cast<int>(word_in);
        std::getline(input_file,word_in,','); // read Eim_error
        std::istringstream(word_in) >> EIM_error;
        std::getline(input_file,word_in,','); // read RB_error_bound
        if (word_in != "")
            std::istringstream(word_in) >> RB_error_bound;
        else
            RB_error_bound = std::sqrt(-1);
        std::getline(input_file,word_in,'\n');
        std::stringstream ss(word_in);
        
        Real temp_double;
        
        while (ss >> temp_double)
        {
            temp_vec.push_back(temp_double);

            if (ss.peek() == ',')
              ss.ignore();
        }
        for (int i = 0; i < temp_vec.size(); i++)
        {
            if (i < temp_vec.size()/2.0)
                param_min.push_back(temp_vec[i]);
            else
                param_max.push_back(temp_vec[i]);
        }
    
        //for (unsigned int i=0; i < number_of_params; i++)
            //std::cout<< param_min[i] << " " << param_max[i] << std::endl;

        // add data read from file to _eim_data_in object
        for (int i = 0; i < param_max.size(); i++)
        {
            _eim_data_in._cont_param_max[i] = param_max[i];
            _eim_data_in._cont_param_min[i] = param_min[i];
        }
        
        _eim_data_in.EIM_error = EIM_error;
        _eim_data_in.RB_error_bound = RB_error_bound;
        
        // use edited _eim_data_in object to create node
        tree = new DwarfElephanthpEIMM_aryTree(_es, _mesh_ptr, _eim_data_in, "online");
       
        tree->root->read_and_extend_hpEIM_tree(_es, _mesh_ptr, _eim_data_in, input_file, children_exist);
        
        input_file.close();
    }
        
    std::vector<std::vector<NumericVector <Number> *> > getOutputs() const;
    

   
//--------------------------------PROTECTED---------------------------------
  protected:

    /* Attributes */
    bool _use_EIM;
    bool _use_hp_EIM;
    bool _use_displaced;
    bool _skip_matrix_assembly_in_rb_system;
    bool _skip_vector_assembly_in_rb_system;
    bool _offline_stage;

    bool _deterministic_training_EIM;
    bool _quiet_mode_EIM;
    bool _normalize_EIM_bound_in_greedy;



    unsigned int _n_training_samples_EIM;
    unsigned int _training_parameters_random_seed_EIM;
    unsigned int _N_max_EIM;

    mutable unsigned int _n_outputs;
    mutable unsigned int _qa;
    mutable unsigned int _qf;
    mutable std::vector<unsigned int> _ql;

    Real _rel_training_tolerance_EIM;
    Real _abs_training_tolerance_EIM;
    std::vector<Real> _continuous_parameter_min_values_EIM;
    std::vector<Real> _continuous_parameter_max_values_EIM;
    std::vector<Real> _discrete_parameter_values_in_EIM;

    std::vector<std::string> _continuous_parameters_EIM;
    std::vector<std::string> _discrete_parameters_EIM;
    std::map<std::string,std::vector<Real>> _discrete_parameter_values_EIM;
    std::string _best_fit_type_EIM;

    EquationSystems & _es;
    MooseMesh * _mesh_ptr;
    //TransientNonlinearImplicitSystem * _sys;
    mutable DwarfElephantRBConstructionSteadyState * _rb_con_ptr;
    DwarfElephantEIMConstructionSteadyState * _eim_con_ptr;
    DwarfElephantRBEvaluationSteadyState *_rb_eval_ptr;
    DwarfElephantEIMEvaluationSteadyState *_eim_eval_ptr;
    //RBSCMConstruction *_rb_scm_con_ptr;
    //RBSCMEvaluation *_rb_scm_eval_ptr;

    SparseMatrix <Number> * _inner_product_matrix_eim;

    mutable SparseMatrix <Number> * _inner_product_matrix;
    mutable std::vector<SparseMatrix <Number> *> _jacobian_subdomain;
    mutable std::vector<NumericVector <Number> *> _residuals;
    mutable std::vector<std::vector<NumericVector <Number> *> > _outputs;

  bool _compliant;
  bool _deterministic_training_RB;
  bool _quiet_mode_RB;
  bool _normalize_RB_bound_in_greedy;

  unsigned int _n_training_samples_RB;
  unsigned int _training_parameters_random_seed_RB;
  unsigned int _N_max_RB;

  std::string _system_name;
//    std::string _parameters_filename;     //only required if one wants to read the data over the GetPot class from libMesh directly
  std::vector<std::string> _continuous_parameters_RB;
  std::vector<std::string> _discrete_parameters_RB;
  std::vector<Real> _discrete_parameter_values_in_RB;
  mutable std::map<std::string,std::vector<Real>> _discrete_parameter_values_RB;

  Real _rel_training_tolerance_RB;
  Real _abs_training_tolerance_RB;
  std::vector<Real> _continuous_parameter_min_values_RB;
  std::vector<Real> _continuous_parameter_max_values_RB;

    //unsigned int _training_parameters_random_seed_SCM;
    
    //Real _training_tolerance_SCM;
    //std::vector<std::string> _continuous_parameters_SCM;
    //std::vector<Real> _continuous_parameter_min_values_SCM;
    //std::vector<Real> _continuous_parameter_max_values_SCM;
    //std::vector<std::string> _discrete_parameters_SCM;
    //std::map<std::string,std::vector<Real>> _discrete_parameter_values_SCM;
    //std::vector<Real> _discrete_parameter_values_in_SCM;

  mutable SparseMatrix <Number> * _RB_inner_product_matrix; // To test against EIM example from Martin's publication
  mutable NumericVector<Number> * _fullFEnonAffineF;

    DwarfElephanthpEIMM_aryTree *_hp_eim_tree_ptr;
    DwarfElephanthpEIMM_aryTree *_online_hp_eim_tree_ptr;
    EIM_input_data _eim_data_in;
    RB_input_data _rb_data_in;
    
    /*Friend Classes*/
    friend class DwarfElephantRBKernel;
    friend class DwarfElephantFTestKernel;
    friend class DwarfElephantRBDiracKernel;
    friend class DwarfElephantRBNodalBC;
    friend class DwarfElephantRBIntegratedBC;
    friend class DwarfElephantOfflineOnlineStageSteadyState;
    friend class DwarfElephantRBEvaluationSteadyState;
    friend class DwarfElephantComputeEIMInnerProductMatrixSteadyState;
    friend class DwarfElephantEIMFKernel;
    friend class DwarfElephantEIMAKernel;
    friend class RBInnerProductMatrix; // To test against EIM example from Martin's publication
    friend class DwarfElephantEIMFKernelsAction;
};
///-------------------------------------------------------------------------
#endif // DWARFELEPHANTINITIALIZERBSYSTEMSTEADYSTATE_H
