import os

directory = os.listdir('.')
os.chdir('.')
pattern = '.m'

for filename in directory:
	matrixBaseName = filename.replace('.m','')
	if pattern in filename:
		with open(filename,'r+') as matFile:
			lines = matFile.readlines()
			lines[4] = lines[4].replace('zzz',matrixBaseName+'_nz')
			lines[5] = lines[5].replace('zzz',matrixBaseName+'_nz')
			lines[-1] = lines[-1].replace('zzz',matrixBaseName+'_nz')
			lastLine = lines[-1].split('=')
			lastLine[0] = matrixBaseName+'_sp'
			lines[-1] = lastLine[0] + '=' + lastLine[1]
			matFile.seek(0)
			matFile.writelines(lines)
			matFile.truncate()
