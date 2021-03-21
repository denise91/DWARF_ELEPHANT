import os, re
import sys


if len(sys.argv) != 2:
  print "Error! Wrong number of command line arguments."

theta_dir_name = sys.argv[1];

directory = os.listdir(theta_dir_name)
os.chdir(theta_dir_name)

#for file in directory:
pattern = "RBTheta"
for filename in directory:
	if pattern in filename:
		with open(filename, "r+") as file:
			lines = file.readlines()
			match = re.search('[(]*[)]',lines[0])
			if (match != None):
				arglist_line = re.split('[()]',lines[0])
				new_arglist = arglist_line[0] + '(mu)' + arglist_line[2]
				lines[0] = new_arglist
				print new_arglist
			else:
				arglist_line = lines[0].split("\n")
				new_arglist = arglist_line[0] + '(mu)\n'
				lines[0] = new_arglist
				print new_arglist
			lines.insert(6,'L = mu("L");\n')
			lines.insert(6,'r = mu("r");\n')
			lines.insert(6,'l = mu("l");\n')
			lines.insert(6,'r_0 = mu("r_0");\n')
			lines.insert(6,'l_0 = mu("l_0");\n')
			lines.insert(6,'d = mu("d");\n')
			lines.insert(6,'h = mu("h");\n')
			lines.insert(6,'k_t = mu("k_t");\n')
			lines.insert(6,'k_b = mu("k_b");\n')
			lines.insert(6,'rho_C_b = mu("rho_C_b");\n')
			lines.insert(6,'rho_C_t = mu("rho_C_t");\n')
			file.seek(0)
			file.writelines(lines)
			file.truncate()

pattern = "RBMTheta"
for filename in directory:
	if pattern in filename:
		with open(filename, "r+") as file:
			lines = file.readlines()
			match = re.search('[(]*[)]',lines[0])
			if (match != None):
				arglist_line = re.split('[()]',lines[0])
				new_arglist = arglist_line[0] + '(mu)' + arglist_line[2]
				lines[0] = new_arglist
				print new_arglist
			else:
				arglist_line = lines[0].split("\n")
				new_arglist = arglist_line[0] + '(mu)\n'
				lines[0] = new_arglist
				print new_arglist
			lines.insert(6,'L = mu("L");\n')
			lines.insert(6,'r = mu("r");\n')
			lines.insert(6,'l = mu("l");\n')
			lines.insert(6,'r_0 = mu("r_0");\n')
			lines.insert(6,'l_0 = mu("l_0");\n')
			lines.insert(6,'d = mu("d");\n')
			lines.insert(6,'h = mu("h");\n')
			lines.insert(6,'k_t = mu("k_t");\n')
			lines.insert(6,'k_b = mu("k_b");\n')
			lines.insert(6,'rho_C_b = mu("rho_C_b");\n')
			lines.insert(6,'rho_C_t = mu("rho_C_t");\n')
			file.seek(0)
			file.writelines(lines)
			file.truncate()
