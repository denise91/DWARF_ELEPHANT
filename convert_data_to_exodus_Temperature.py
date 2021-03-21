# trace generated using paraview version 5.5.2

#### import the simple module from the paraview
from paraview.simple import *
#### disable automatic camera reset on 'Show'
paraview.simple._DisableFirstRenderCameraReset()

mesh_labels = {'min_min':['Min','Ref','Max'],'min_max':['Min','Ref','Max'],'max_min':['Min','Ref','Max'],'max_max':['Min','Ref','Max']}

for i, param_subd in enumerate(list(mesh_labels)):
  for j, param_val_str in enumerate(mesh_labels[param_subd]):
    # create a new 'XML Unstructured Grid Reader'
    temperature_2160vtu = XMLUnstructuredGridReader(FileName=['/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/PDSplit/'+param_subd+'/param'+param_val_str+'/mesh2/temperature_2160.vtu'])
    temperature_2160vtu.CellArrayStatus = ['subdomain_id']
    temperature_2160vtu.PointArrayStatus = ['temperature']
    
    # Properties modified on temperature_2160vtu
    temperature_2160vtu.CellArrayStatus = []
    
    # get active view
    renderView1 = GetActiveViewOrCreate('RenderView')
    # uncomment following to set a specific view size
    # renderView1.ViewSize = [1214, 519]
    
    # show data in view
    temperature_2160vtuDisplay = Show(temperature_2160vtu, renderView1)
    
    # trace defaults for the display properties.
    temperature_2160vtuDisplay.Representation = 'Surface'
    temperature_2160vtuDisplay.ColorArrayName = [None, '']
    temperature_2160vtuDisplay.OSPRayScaleArray = 'temperature'
    temperature_2160vtuDisplay.OSPRayScaleFunction = 'PiecewiseFunction'
    temperature_2160vtuDisplay.SelectOrientationVectors = 'None'
    temperature_2160vtuDisplay.ScaleFactor = 0.010000000000000002
    temperature_2160vtuDisplay.SelectScaleArray = 'None'
    temperature_2160vtuDisplay.GlyphType = 'Arrow'
    temperature_2160vtuDisplay.GlyphTableIndexArray = 'None'
    temperature_2160vtuDisplay.GaussianRadius = 0.0005
    temperature_2160vtuDisplay.SetScaleArray = ['POINTS', 'temperature']
    temperature_2160vtuDisplay.ScaleTransferFunction = 'PiecewiseFunction'
    temperature_2160vtuDisplay.OpacityArray = ['POINTS', 'temperature']
    temperature_2160vtuDisplay.OpacityTransferFunction = 'PiecewiseFunction'
    temperature_2160vtuDisplay.DataAxesGrid = 'GridAxesRepresentation'
    temperature_2160vtuDisplay.SelectionCellLabelFontFile = ''
    temperature_2160vtuDisplay.SelectionPointLabelFontFile = ''
    temperature_2160vtuDisplay.PolarAxes = 'PolarAxesRepresentation'
    temperature_2160vtuDisplay.ScalarOpacityUnitDistance = 0.0015003986000533295
    
    # init the 'PiecewiseFunction' selected for 'ScaleTransferFunction'
    temperature_2160vtuDisplay.ScaleTransferFunction.Points = [310.15, 0.0, 0.5, 0.0, 369.7418, 1.0, 0.5, 0.0]
    
    # init the 'PiecewiseFunction' selected for 'OpacityTransferFunction'
    temperature_2160vtuDisplay.OpacityTransferFunction.Points = [310.15, 0.0, 0.5, 0.0, 369.7418, 1.0, 0.5, 0.0]
    
    # init the 'GridAxesRepresentation' selected for 'DataAxesGrid'
    temperature_2160vtuDisplay.DataAxesGrid.XTitleFontFile = ''
    temperature_2160vtuDisplay.DataAxesGrid.YTitleFontFile = ''
    temperature_2160vtuDisplay.DataAxesGrid.ZTitleFontFile = ''
    temperature_2160vtuDisplay.DataAxesGrid.XLabelFontFile = ''
    temperature_2160vtuDisplay.DataAxesGrid.YLabelFontFile = ''
    temperature_2160vtuDisplay.DataAxesGrid.ZLabelFontFile = ''
    
    # init the 'PolarAxesRepresentation' selected for 'PolarAxes'
    temperature_2160vtuDisplay.PolarAxes.PolarAxisTitleFontFile = ''
    temperature_2160vtuDisplay.PolarAxes.PolarAxisLabelFontFile = ''
    temperature_2160vtuDisplay.PolarAxes.LastRadialAxisTextFontFile = ''
    temperature_2160vtuDisplay.PolarAxes.SecondaryRadialAxesTextFontFile = ''
    
    # reset view to fit data
    renderView1.ResetCamera()
    
    # update the view to ensure updated data information
    renderView1.Update()
    
    # save data
    SaveData('/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/PDSplit/'+param_subd+'/param'+param_val_str+'/mesh2/temperature_2160.e', proxy=temperature_2160vtu)
    
    #### saving camera placements for all active views
    
    # current camera placement for renderView1
    renderView1.CameraPosition = [0.0, 0.0, 0.33460652149512327]
    renderView1.CameraParallelScale = 0.08660254037844388
    
    #### uncomment the following to render all views
    # RenderAllViews()
    # alternatively, if you want to write images, you can use SaveScreenshot(...).
