#! /bin/sh

for dir in mesh*; do
  cd ./${dir}
  python /home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/python_scripts/extractNonZeros.py
  echo "Now renaming files"
  for file in *.m; do
    echo "${File}"
    mv "${file}" "${file/.m/.txt}"
  done
  cd ../
done
