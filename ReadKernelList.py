with open("test_Kernels_list.txt","r") as KernelList_File:
  KernelList_lines = KernelList_File.readlines()

KernelIDs_and_blocks = []

for i in range(len(KernelList_lines)):
  if KernelList_lines[i].find(" type") != -1:
    temp_list = KernelList_lines[i].split(" type = ")
    KernelID = temp_list[1].strip('\n')
    print KernelID
  if KernelList_lines[i].find("block") != -1:
    temp_list = KernelList_lines[i].split("block = ")
    block = temp_list[1].strip('\n')
    KernelIDs_and_blocks.append([KernelID,block])

print KernelIDs_and_blocks
