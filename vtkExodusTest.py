#!/usr/bin/env python
#
# This example was built using Python2.7 and VTK6.3 on OSX
# Computes relative error made by RB/RBEIM approximation wrt FE truth in L-infinity norm
# Uses vtk to read exodusII file and manipulate read data

from vtk import *
import numpy as np
import matplotlib.pyplot as plt

def GetRequiredArray(FileName,ArrayName):
  """ Get array ArrayName (string) from single block exodus file FileName""" 
  ArrayNameFlag = 0
  rdr = vtkExodusIIReader()
  rdr.SetFileName( FileName ) # or whatever
  rdr.UpdateInformation() # this tells the reader to fetch metadata from the file
  # Iterate over all the point arrays:
  for i in range( rdr.GetNumberOfObjectArrays( rdr.NODAL ) ):
    nname = rdr.GetObjectArrayName( rdr.NODAL, i )
    #print 'Array %d is "%s"' % (i,nname)
    # if an array name matches, tell the reader we want to load it:
    if nname == ArrayName:
      # 0 means "don't load", 1 means "load" the i-th nodal array
      rdr.SetObjectArrayStatus( rdr.NODAL, i, 1 )
      ArrayNameFlag = 1
  rdr.Update()
  out = rdr.GetOutput() # out is a vtkMultiBlockDataSet
  if (ArrayNameFlag == 0):
    print "Error: GetRequiredArray: Variable named ", ArrayName, " not found in exodus file ",FileName
    quit()
  elem_blks = out.GetBlock( 0 ) # elem_blks is a vtkDataObject
  NumElementBlocks = elem_blks.GetNumberOfBlocks()
  RequiredArray = []
  for i in range(NumElementBlocks):
    RequiredArray.append( elem_blks.GetBlock(i).GetPointData().GetArray( ArrayName ) )

  return RequiredArray

def SubtractvtkDoubleArrays(Array1, Array2, ResultArrayName):
  """ Returns Array1 - Array2 as a vtkDoubleArray
      Array1 : vtkDoubleArray
      Array2 : vtkDoubleArray 
      ResultArrayName : String (name of result vtkDoubleArray)"""
  if (Array1.GetSize() != Array2.GetSize()) or (Array1.GetNumberOfComponents() != Array2.GetNumberOfComponents()):
    print "Error from SubtractvtkDoubleArrays: Input Arrays not of same size/components"
  ArraySize = Array1.GetSize()
  ArrayNumberOfComponents = Array1.GetNumberOfComponents()
  result = vtkDoubleArray()
  result.SetName(ResultArrayName)
  result.SetNumberOfComponents(ArrayNumberOfComponents)
 
  for i in range(ArraySize):
   for j in range(ArrayNumberOfComponents):
     result.InsertComponent(j, i, Array1.GetTuple(i)[j] - Array2.GetTuple(i)[j])

  return result

def ComputeRBRelError_LinftyNorm(FEsoln, N, RBArrayName, RBExodusFileBaseName):
  """ Compute RB relative error in L-infinity norm for give N 
      Input Parameters
      FEsoln: FE solution in vtkDoubleArray format 
      N: size of Reduced basis """
  FileName = RBExodusFileBaseName+str(N).zfill(2)

  ArrayName = RBArrayName
  Temperature_RB = GetRequiredArray(FileName,ArrayName)
  if (len(u) != len(Temperature_RB)):
    print "Error: Compute RBRelError_LinftyNorm : FE and RB solutions have different numbers of subdomains"
    quit()
  
  AbsoluteError = []
  AbsoluteError_LinftyNorm = 0.0
  FEsoln_LinftyNorm = 0.0
  for i in range(len(u)):
    AbsoluteError.append( SubtractvtkDoubleArrays(u[i], Temperature_RB[i], 'Difference') )
    if (AbsoluteError_LinftyNorm < AbsoluteError[i].GetMaxNorm()):
      AbsoluteError_LinftyNorm = AbsoluteError[i].GetMaxNorm()
    if (FEsoln_LinftyNorm < u[i].GetMaxNorm()):
      FEsoln_LinftyNorm = u[i].GetMaxNorm()
 
  return AbsoluteError_LinftyNorm/FEsoln_LinftyNorm

FileName = '/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/my_app/ModifiedPennesPerfuison/ModifiedPennesPerfusion_out.e'
ArrayName = 'T'
u = GetRequiredArray(FileName,ArrayName)
RBArrayName = 'temperature(RB)'
RBExodusFileBaseName = 'ModifiedPerfusionRB_soln.e-s'

N = 5
RelError_LinftyNorm = np.array([])
N_array = np.array([])
for n in range(1,N+1):
   RelError_LinftyNorm = np.append(RelError_LinftyNorm, ComputeRBRelError_LinftyNorm(u, n, RBArrayName, RBExodusFileBaseName))
   N_array = np.append(N_array, n)


plt.semilogy(N_array, RelError_LinftyNorm)
plt.xlabel('N', fontsize = 18)
plt.ylabel('$||u_{FE} - u_{RB}||_{L_\infty}/||u_{FE}||_{L_\infty}$', fontsize=18)
plt.xticks(fontsize=14)
plt.yticks(fontsize=14)
plt.show()

