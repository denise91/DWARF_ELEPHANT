#! /bin/sh -p
#PBS -l nodes=1:ppn=6
#PBS -N RBMeshConv_paramRef


/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/moose/3RD/bin/mpiexec -n 6 /home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/DwarfElephant-opt --timing -i /home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/RBRFA3DMeshConv_needle_theta1.57_phi0.0_r00.003_l00.04_mesh_${PBS_ARRAYID}.i

for TISSUEDAMAGEFILE in tissue_damage_r0_0_[0-9].vtu; do
    mv ${TISSUEDAMAGEFILE} ${TISSUEDAMAGEFILE/0_0/0_0.003_l0_0.04_mesh_${PBS_ARRAYID}}
done
