/**
 * This UserObject implements the Offline and Online stage of the RB method
 * for the steady state case.
 */

///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTOFFLINEONLINESTAGESTEADYSTATE_H
#define DWARFELEPHANTOFFLINEONLINESTAGESTEADYSTATE_H

///---------------------------------INCLUDES--------------------------------
//libMesh includes
#include "libmesh/equation_systems.h"
#include "libmesh/sparse_matrix.h"

// MOOSE includes
#include "GeneralUserObject.h"
#include "DisplacedProblem.h"
#include "MooseMesh.h"
#include "MooseVariable.h"
#include "NonlinearSystemBase.h"
#include "NodalBC.h"
#include "Assembly.h"

// MOOSE includes (DwarfElephant package)
#include "DwarfElephantRBClassesSteadyState.h"
#include "DwarfElephantInitializeRBSystemSteadyState.h"
#include "DwarfElephantRBProblem.h"


///-------------------------------------------------------------------------
// Forward Declarations
namespace libMesh
{
  class EquationSystems;
  template <typename T> class SparseMatrix;
}

class MooseMesh;
class NonlinearSystemBase;
class Assembly;
class DwarfElephantOfflineOnlineStageSteadyState;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantOfflineOnlineStageSteadyState>();

///-------------------------------------------------------------------------
class DwarfElephantOfflineOnlineStageSteadyState :
  public GeneralUserObject
{

//----------------------------------PUBLIC----------------------------------
  public:
    DwarfElephantOfflineOnlineStageSteadyState(const InputParameters & params);


    /* Methods */
    void setAffineMatrices();
    void offlineStageEIM();
    void offlineStageRBOnly();
    void onlineStageEIM();
    void onlineStageRBOnly();
    void setOnlineParameters();
    void transferAffineVectors();
//    std::string getFileName();

    virtual void initialize() override;
    virtual void execute() override;
    virtual void finalize() override;
    
    void read_and_create_hpEIM_tree(EquationSystems & _es, MooseMesh * _mesh_ptr, EIM_input_data _eim_data_in, std::string filename, DwarfElephanthpEIMM_aryTree* & tree)
    // Reads file with given name to construct hp EIM tree based on the information therein
    // The "_online_hp_eim_tree_ptr" member of this class points to the tree object that this function creates
    {
        std::ifstream input_file;
        bool children_exist;
        int number_of_params;
        std::vector<Real> param_min, param_max;
        input_file.open(filename);
    
        std::vector<Real> temp_vec;
        std::string word_in;
        std::getline(input_file,word_in,','); // read child_exist flag
        children_exist = boost::lexical_cast<bool>(word_in);
        std::getline(input_file,word_in,',');
        number_of_params = boost::lexical_cast<int>(word_in);
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
    
        std::cout << children_exist << " " << number_of_params << " ";
        for (unsigned int i=0; i < number_of_params; i++)
            std::cout<< param_min[i] << " " << param_max[i] << std::endl;

        // add data read from file to _eim_data_in object
        for (int i = 0; i < param_max.size(); i++)
        {
            _eim_data_in._cont_param_max[i] = param_max[i];
            _eim_data_in._cont_param_min[i] = param_min[i];
        }
        std::cout << param_max[0] << " " << param_min[0] << std::endl;
        // use edited _eim_data_in object to create node
        tree = new DwarfElephanthpEIMM_aryTree(_es, _mesh_ptr, _eim_data_in, "online");
       
        tree->root->read_and_extend_hpEIM_tree(_es, _mesh_ptr, _eim_data_in, input_file, children_exist);
        
        input_file.close();
    }

    ~DwarfElephantOfflineOnlineStageSteadyState()
    {
        //delete _online_hp_eim_tree_ptr;
    }
//--------------------------------PROTECTED---------------------------------
  protected:

    /* Attributes */
    bool _use_displaced;
    bool _store_basis_functions;
    bool _skip_matrix_assembly_in_rb_system;
    bool _skip_vector_assembly_in_rb_system;
    bool _compliant;
    bool _online_stage;
    bool _offline_error_bound;
    bool _output_file;
    bool _compute_output;
    bool _output_console;
    bool _output_csv;

    bool _norm_online_values;

    unsigned int _norm_id;
    unsigned int _n_outputs;
    unsigned int _online_N;

    std::string _system_name;

    EquationSystems & _es;
    TransientNonlinearImplicitSystem & _sys;
    const DwarfElephantInitializeRBSystemSteadyState & _initialize_rb_system;

    MooseMesh * _mesh_ptr;

    const std::set<SubdomainID> & _subdomain_ids;
    std::vector<Number> _RB_outputs;

    Real _mu_bar;
    std::vector<Real> _online_mu_parameters;

    RBParameters _rb_online_mu;

    DwarfElephantRBProblem * _rb_problem;
    
    DwarfElephanthpEIMM_aryTree *_online_hp_eim_tree_ptr;

    friend class DwarfElephantDakotaOutput;
};
///-------------------------------------------------------------------------
#endif // DWARFELEPHANTOFFLINEONLINESTAGESTEADYSTATE_H
