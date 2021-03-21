function [rss, vmem] = get_memory_usage()
proc_stat_str = fileread('/proc/self/stat');
proc_stat_ca = strsplit(proc_stat_str);
rss = str2double(proc_stat_ca{24})/10^6; % Mb
vmem = str2double(proc_stat_ca{23})/10^6; % Mb
end
