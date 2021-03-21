function [] = get_memory_usage_from_qstat()      
      [status1,qstat_mem_raw] = system('qstat -f ${PBS_JOBID} | grep "resources_used.mem"');
      [status2,qstat_vmem_raw] = system('qstat -f ${PBS_JOBID} | grep "resources_used.vmem"');
      pattern='\d+';
      qstat_mem=regexp(qstat_mem_raw,pattern,'match');
      qstat_vmem=regexp(qstat_vmem_raw,pattern,'match');
      if ((status1 == 0) && (status2 == 0))
        fprintf(1,"Memory consumption from qstat: mem=%e Mb; vmem=%e Mb;\n",str2double(qstat_mem{1})/1e3,str2double(qstat_vmem{1})/1e3);
      end
end
