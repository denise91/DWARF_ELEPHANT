function [online_mu_cell_arr] = get_online_mu_list(filename)
  mu_file = fopen(filename);
  keys_line = fgetl(mu_file);
  keys_arr = split(strtrim(keys_line));
  online_mu_cell_arr = cell(1,1);
  i = 0;
  while (true)
    vals_line = fgetl(mu_file);
    if (vals_line == -1)
      break
    end
    i = i + 1;
    vals_arr = split(strtrim(vals_line));
    if (max(size(keys_arr)) ~= max(size(vals_arr)))
      error('Number of param vals and params keys does not match. Check online param list file.\n');
    end
    if (max(size(keys_arr)) ~= 15)
      error('Not enough parameters. Check online param list file.\n'); 
    end
    online_mu_cell_arr{i} = containers.Map;
    online_mu_cell_arr{i} = containers.Map('KeyType','char','ValueType','any');
    for j = 1:size(keys_arr)
      val = vals_arr(j);
      key = keys_arr(j);
      online_mu_cell_arr{i}(key{1}) = str2double(val{1});
    end
    online_mu_cell_arr{i}('L') = 0.1;
    online_mu_cell_arr{i}('r') = 0.001414;                     
    online_mu_cell_arr{i}('l') = 0.01871;                      
    online_mu_cell_arr{i}('d') = (8.0/3.0)*online_mu_cell_arr{i}('r');
    online_mu_cell_arr{i}('h') = (4.0/3.0)*online_mu_cell_arr{i}('l');
  end
end
