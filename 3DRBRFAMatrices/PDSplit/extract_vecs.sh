for par_dir in ./m*_m*/F_vectors; do
  cd ./${par_dir}
  for dir in param_*/mesh*; do
    cd ./${dir}
    echo "Extracting numerical data from .m files to .txt files"
    for m_file in ./*.m; do
      grep -E "^[0-9-]" ${m_file} > ${m_file/.m/.txt}
    done
    #echo "Deleting old .m files"
    #for file in ./*.m; do
    #  echo "${dir}" "${file}"
    #  rm "${file}"
    #done
    cd ../../
  done
  cd ../../
done
