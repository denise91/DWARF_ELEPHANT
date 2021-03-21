#!/bin/sh
# Shell script to exract matrix entries from a libmesh-written .m file to a txt file
for par_dir in ./m*_m*; do
  cd ./${par_dir}
    for dir in mesh*; do
      cd ./${dir}
      echo "Extracting numerical data from .m files into .txt files"
      for m_file in ./*.m; do
        grep -E "^[0-9]" ${m_file} > ${m_file/.m/.txt}
      done
      echo "Now deleting old .m files"
      for file in ./*.m; do
        echo "${file}"
        rm "${file}"
      done
      cd ../
    done
  cd ../
done
