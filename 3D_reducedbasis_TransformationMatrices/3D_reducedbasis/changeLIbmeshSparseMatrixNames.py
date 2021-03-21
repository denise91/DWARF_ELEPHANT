import os

directory = os.listdir('.')
os.chdir('.')

for filename in directory:
	with open(filename,'r+') as matFile:
		lines = matFile.readlines()
		