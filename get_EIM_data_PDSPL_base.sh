#! /bin/sh -p
#PBS -l nodes=1:ppn=3
#PBS -N get_EIM_{param_str}


/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/DwarfElephant-opt --timing -i /home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/Obtain_EIM_data_PDSPL_{param_str}.i
