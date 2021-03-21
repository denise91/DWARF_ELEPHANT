#!/bin/ksh

cd ./3DRBRFAMatrices/MeshConvMatrices/transienttestcase/F_vectors/mesh4

for file in ./Fq_*.m; do
  grep -E "^[0-9-]" ${file} > ${file/.m/.txt}
done

cd ../../../../../
