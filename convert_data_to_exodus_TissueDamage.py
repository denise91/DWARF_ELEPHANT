# trace generated using paraview version 5.5.2

#### import the simple module from the paraview
from paraview.simple import *
#### disable automatic camera reset on 'Show'
paraview.simple._DisableFirstRenderCameraReset()

mesh_labels = {'min_min':['Min','Ref','Max'],'min_max':['Min','Ref','Max'],'max_min':['Min','Ref','Max'],'max_max':['Min','Ref','Max']}

for i, param_subd in enumerate(list(mesh_labels)):
  for j, param_val_str in enumerate(mesh_labels[param_subd]):
    # create a new 'XML Unstructured Grid Reader'
    arrh_tissue_damagevtu = XMLUnstructuredGridReader(FileName=['/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/PDSplit/'+param_subd+'/param'+param_val_str+'/mesh2/Arrh_tissue_damage.vtu'])
    arrh_tissue_damagevtu.PointArrayStatus = ['arrhenius_tissue_damage']
    
    # get active view
    renderView1 = GetActiveViewOrCreate('RenderView')
    # uncomment following to set a specific view size
    # renderView1.ViewSize = [1214, 519]
    
    # show data in view
    arrh_tissue_damagevtuDisplay = Show(arrh_tissue_damagevtu, renderView1)
    
    # trace defaults for the display properties.
    arrh_tissue_damagevtuDisplay.Representation = 'Surface'
    arrh_tissue_damagevtuDisplay.ColorArrayName = [None, '']
    arrh_tissue_damagevtuDisplay.OSPRayScaleArray = 'arrhenius_tissue_damage'
    arrh_tissue_damagevtuDisplay.OSPRayScaleFunction = 'PiecewiseFunction'
    arrh_tissue_damagevtuDisplay.SelectOrientationVectors = 'None'
    arrh_tissue_damagevtuDisplay.ScaleFactor = 0.010000000000000002
    arrh_tissue_damagevtuDisplay.SelectScaleArray = 'None'
    arrh_tissue_damagevtuDisplay.GlyphType = 'Arrow'
    arrh_tissue_damagevtuDisplay.GlyphTableIndexArray = 'None'
    arrh_tissue_damagevtuDisplay.GaussianRadius = 0.0005
    arrh_tissue_damagevtuDisplay.SetScaleArray = ['POINTS', 'arrhenius_tissue_damage']
    arrh_tissue_damagevtuDisplay.ScaleTransferFunction = 'PiecewiseFunction'
    arrh_tissue_damagevtuDisplay.OpacityArray = ['POINTS', 'arrhenius_tissue_damage']
    arrh_tissue_damagevtuDisplay.OpacityTransferFunction = 'PiecewiseFunction'
    arrh_tissue_damagevtuDisplay.DataAxesGrid = 'GridAxesRepresentation'
    arrh_tissue_damagevtuDisplay.SelectionCellLabelFontFile = ''
    arrh_tissue_damagevtuDisplay.SelectionPointLabelFontFile = ''
    arrh_tissue_damagevtuDisplay.PolarAxes = 'PolarAxesRepresentation'
    arrh_tissue_damagevtuDisplay.ScalarOpacityUnitDistance = 0.0015003986000533295
    
    # init the 'GridAxesRepresentation' selected for 'DataAxesGrid'
    arrh_tissue_damagevtuDisplay.DataAxesGrid.XTitleFontFile = ''
    arrh_tissue_damagevtuDisplay.DataAxesGrid.YTitleFontFile = ''
    arrh_tissue_damagevtuDisplay.DataAxesGrid.ZTitleFontFile = ''
    arrh_tissue_damagevtuDisplay.DataAxesGrid.XLabelFontFile = ''
    arrh_tissue_damagevtuDisplay.DataAxesGrid.YLabelFontFile = ''
    arrh_tissue_damagevtuDisplay.DataAxesGrid.ZLabelFontFile = ''
    
    # init the 'PolarAxesRepresentation' selected for 'PolarAxes'
    arrh_tissue_damagevtuDisplay.PolarAxes.PolarAxisTitleFontFile = ''
    arrh_tissue_damagevtuDisplay.PolarAxes.PolarAxisLabelFontFile = ''
    arrh_tissue_damagevtuDisplay.PolarAxes.LastRadialAxisTextFontFile = ''
    arrh_tissue_damagevtuDisplay.PolarAxes.SecondaryRadialAxesTextFontFile = ''
    
    # reset view to fit data
    renderView1.ResetCamera()
    
    # update the view to ensure updated data information
    renderView1.Update()
    
    # save data
    SaveData('/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/PDSplit/'+param_subd+'/param'+param_val_str+'/mesh2/Arrh_tissue_damage.e', proxy=arrh_tissue_damagevtu)
    
    #### saving camera placements for all active views
    
    # current camera placement for renderView1
    renderView1.CameraPosition = [0.0, 0.0, 0.33460652149512327]
    renderView1.CameraParallelScale = 0.08660254037844388
    
    #### uncomment the following to render all views
    # RenderAllViews()
    # alternatively, if you want to write images, you can use SaveScreenshot(...).
