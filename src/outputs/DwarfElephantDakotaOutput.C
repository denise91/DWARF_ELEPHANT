// MOOSE includes
#include "NonlinearSystemBase.h"
#include "FEProblem.h"

#include "DwarfElephantDakotaOutput.h"

registerMooseObject("DwarfElephantApp", DwarfElephantDakotaOutput);

template <>
InputParameters
validParams<DwarfElephantDakotaOutput>()
{
  InputParameters params = validParams<FileOutput>();
  params.addParam<std::vector<PostprocessorName>>("postprocessor","Defines the name of the postprocessor(s) you want to use.");
  params.addParam<std::string>("delimiter", "   ", "Defines the delimiter.");
  params.addParam<std::string>("add_on", "f", "Defines the additional idientifier.");
  params.addParam<std::string>("simulation_type", "steady", "Determines whether the simulation is steady state or transient.");
  params.addParam<bool>("use_rb", false, "Defines whether the RB or FE method is used.");
  params.addParam<UserObjectName>("offline_online_rb_userobject", "Name of the UserObject for the  offline and online stage of the RB system");

  return params;
}

DwarfElephantDakotaOutput::DwarfElephantDakotaOutput(const InputParameters & parameters) :
    FileOutput(parameters),
    _delimiter(getParam<std::string>("delimiter")),
    _add_on(getParam<std::string>("add_on")),
    _simulation_type(getParam<std::string>("simulation_type")),
    _use_rb(getParam<bool>("use_rb"))
{
  std::ifstream input_file(filename());

  if (input_file)
  {
    remove(filename().c_str());
  }

  if(_use_rb)
    _offline_online_rb_system_name = getParam<UserObjectName>("offline_online_rb_userobject");
  else
    _postprocessor_name = getParam<std::vector<PostprocessorName>>("postprocessor");
}

void
DwarfElephantDakotaOutput::output(const ExecFlagType & /*type*/)
{
  Moose::perf_log.push("DakotaOutput()", "Output");
  // This result file enables the use of MOOSE as a forward simulator within Dakota.
  // Which output parameters are printed to the result file can be controlled over the MOOSE input file.

  if(processor_id() == 0){
    std::ofstream dakota_file;
    dakota_file.open(filename().c_str(), std::ios::app);

    if(!_use_rb)
    {
      for(unsigned int i = 0; i < _postprocessor_name.size(); i++)
        // if(i < _postprocessor_name.size()-1)
        //   dakota_file << _problem_ptr->getPostprocessorValue(_postprocessor_name[i]) << " " << _add_on << _delimiter;
        // else
          dakota_file << _problem_ptr->getPostprocessorValueByName(_postprocessor_name[i]) << " " << _add_on << std::endl;
    } else {
      if(_simulation_type == "steady")
      {
        DwarfElephantOfflineOnlineStageSteadyState & _offline_online_rb_system = _problem_ptr->getUserObject<DwarfElephantOfflineOnlineStageSteadyState>(_offline_online_rb_system_name);

        if (_offline_online_rb_system._output_file)
         mooseError("This Output class using the RB method is specifically designed to work efficiently for repetitive forward simulations. Therefore the output of Exodus files is not desired and the combination of outputting Exodus files and DakotaOutputs is therefore not supported.");

        if (!_offline_online_rb_system._output_csv)
          mooseError("In order to use this Output class you have to set 'output_csv' in the " + _offline_online_rb_system_name + " UserObject to true.");

        for (unsigned int i = 0; i != _offline_online_rb_system._n_outputs; i++)
          // if(i < _offline_online_rb_system._n_outputs-1)
          //   dakota_file << _offline_online_rb_system._RB_outputs[i] << " " << _add_on << _delimiter;
          // else
            dakota_file << _offline_online_rb_system._RB_outputs[i] << " " << _add_on << std::endl;
      } else{
        DwarfElephantOfflineOnlineStageTransient & _offline_online_rb_system = _problem_ptr->getUserObject<DwarfElephantOfflineOnlineStageTransient>(_offline_online_rb_system_name);

        if (_offline_online_rb_system._output_file)
         mooseError("This Output class using the RB method is specifically designed to work efficiently for repetitive forward simulations. Therefore the output of Exodus files is not desired and the combination of outputting Exodus files and DakotaOutputs is therefore not supported.");

        if (!_offline_online_rb_system._output_csv)
          mooseError("In order to use this Output class you have to set 'output_csv' in the " + _offline_online_rb_system_name + " UserObject to true.");

        for (unsigned int _time_step = 0; _time_step <= _offline_online_rb_system._n_time_steps; _time_step++)
        {
          for (unsigned int i = 0; i < _offline_online_rb_system._n_outputs; i++)
          {
            // if(i < _offline_online_rb_system._n_outputs-1)
            //   dakota_file << _offline_online_rb_system._RB_outputs_all_timesteps[_time_step][i] << " " << _add_on << _delimiter;
            // else
              dakota_file << _offline_online_rb_system._RB_outputs_all_timesteps[_time_step][i] << " " << _add_on << std::endl;
            }
         }
      }
    }

    dakota_file.close();
  }
  Moose::perf_log.pop("DakotaOutput()", "Output");
}
