# trace generated using paraview version 5.5.2

#### import the simple module from the paraview
from paraview.simple import *
#### disable automatic camera reset on 'Show'
paraview.simple._DisableFirstRenderCameraReset()

# create a new 'ExodusIIReader'
advectionDiffusionModel_3D_meshConv_0_oute = ExodusIIReader(FileName=['/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/my_app/ModifiedPennesPerfusion/AdvectionDiffusionModel_3D_meshConv_0_out.e'])
advectionDiffusionModel_3D_meshConv_0_oute.PointVariables = []
advectionDiffusionModel_3D_meshConv_0_oute.GlobalVariables = []
advectionDiffusionModel_3D_meshConv_0_oute.NodeSetArrayStatus = []
advectionDiffusionModel_3D_meshConv_0_oute.SideSetArrayStatus = []

# get animation scene
animationScene1 = GetAnimationScene()

# update animation scene based on data timesteps
animationScene1.UpdateAnimationUsingDataTimeSteps()

# Properties modified on advectionDiffusionModel_3D_meshConv_0_oute
advectionDiffusionModel_3D_meshConv_0_oute.GenerateObjectIdCellArray = 0
advectionDiffusionModel_3D_meshConv_0_oute.GenerateGlobalElementIdArray = 0
advectionDiffusionModel_3D_meshConv_0_oute.GenerateGlobalNodeIdArray = 0
advectionDiffusionModel_3D_meshConv_0_oute.PointVariables = ['ThermalDamage']
advectionDiffusionModel_3D_meshConv_0_oute.ElementBlocks = ['phantom', 'vessel', 'needle']

# get active view
renderView1 = GetActiveViewOrCreate('RenderView')
# uncomment following to set a specific view size
# renderView1.ViewSize = [1423, 630]

# show data in view
advectionDiffusionModel_3D_meshConv_0_outeDisplay = Show(advectionDiffusionModel_3D_meshConv_0_oute, renderView1)

# trace defaults for the display properties.
advectionDiffusionModel_3D_meshConv_0_outeDisplay.Representation = 'Surface'
advectionDiffusionModel_3D_meshConv_0_outeDisplay.ColorArrayName = [None, '']
advectionDiffusionModel_3D_meshConv_0_outeDisplay.OSPRayScaleArray = 'ThermalDamage'
advectionDiffusionModel_3D_meshConv_0_outeDisplay.OSPRayScaleFunction = 'PiecewiseFunction'
advectionDiffusionModel_3D_meshConv_0_outeDisplay.SelectOrientationVectors = 'None'
advectionDiffusionModel_3D_meshConv_0_outeDisplay.ScaleFactor = 0.010000000149011612
advectionDiffusionModel_3D_meshConv_0_outeDisplay.SelectScaleArray = 'None'
advectionDiffusionModel_3D_meshConv_0_outeDisplay.GlyphType = 'Arrow'
advectionDiffusionModel_3D_meshConv_0_outeDisplay.GlyphTableIndexArray = 'None'
advectionDiffusionModel_3D_meshConv_0_outeDisplay.GaussianRadius = 0.0005000000074505806
advectionDiffusionModel_3D_meshConv_0_outeDisplay.SetScaleArray = ['POINTS', 'ThermalDamage']
advectionDiffusionModel_3D_meshConv_0_outeDisplay.ScaleTransferFunction = 'PiecewiseFunction'
advectionDiffusionModel_3D_meshConv_0_outeDisplay.OpacityArray = ['POINTS', 'ThermalDamage']
advectionDiffusionModel_3D_meshConv_0_outeDisplay.OpacityTransferFunction = 'PiecewiseFunction'
advectionDiffusionModel_3D_meshConv_0_outeDisplay.DataAxesGrid = 'GridAxesRepresentation'
advectionDiffusionModel_3D_meshConv_0_outeDisplay.SelectionCellLabelFontFile = ''
advectionDiffusionModel_3D_meshConv_0_outeDisplay.SelectionPointLabelFontFile = ''
advectionDiffusionModel_3D_meshConv_0_outeDisplay.PolarAxes = 'PolarAxesRepresentation'
advectionDiffusionModel_3D_meshConv_0_outeDisplay.ScalarOpacityUnitDistance = 0.004239950101825001

# init the 'PiecewiseFunction' selected for 'ScaleTransferFunction'
advectionDiffusionModel_3D_meshConv_0_outeDisplay.ScaleTransferFunction.Points = [0.0, 0.0, 0.5, 0.0, 1.1757813367477812e-38, 1.0, 0.5, 0.0]

# init the 'PiecewiseFunction' selected for 'OpacityTransferFunction'
advectionDiffusionModel_3D_meshConv_0_outeDisplay.OpacityTransferFunction.Points = [0.0, 0.0, 0.5, 0.0, 1.1757813367477812e-38, 1.0, 0.5, 0.0]

# init the 'GridAxesRepresentation' selected for 'DataAxesGrid'
advectionDiffusionModel_3D_meshConv_0_outeDisplay.DataAxesGrid.XTitleFontFile = ''
advectionDiffusionModel_3D_meshConv_0_outeDisplay.DataAxesGrid.YTitleFontFile = ''
advectionDiffusionModel_3D_meshConv_0_outeDisplay.DataAxesGrid.ZTitleFontFile = ''
advectionDiffusionModel_3D_meshConv_0_outeDisplay.DataAxesGrid.XLabelFontFile = ''
advectionDiffusionModel_3D_meshConv_0_outeDisplay.DataAxesGrid.YLabelFontFile = ''
advectionDiffusionModel_3D_meshConv_0_outeDisplay.DataAxesGrid.ZLabelFontFile = ''

# init the 'PolarAxesRepresentation' selected for 'PolarAxes'
advectionDiffusionModel_3D_meshConv_0_outeDisplay.PolarAxes.PolarAxisTitleFontFile = ''
advectionDiffusionModel_3D_meshConv_0_outeDisplay.PolarAxes.PolarAxisLabelFontFile = ''
advectionDiffusionModel_3D_meshConv_0_outeDisplay.PolarAxes.LastRadialAxisTextFontFile = ''
advectionDiffusionModel_3D_meshConv_0_outeDisplay.PolarAxes.SecondaryRadialAxesTextFontFile = ''

# reset view to fit data
renderView1.ResetCamera()

# update the view to ensure updated data information
renderView1.Update()

# set scalar coloring
ColorBy(advectionDiffusionModel_3D_meshConv_0_outeDisplay, ('FIELD', 'vtkBlockColors'))

# show color bar/color legend
advectionDiffusionModel_3D_meshConv_0_outeDisplay.SetScalarBarVisibility(renderView1, True)

# get color transfer function/color map for 'vtkBlockColors'
vtkBlockColorsLUT = GetColorTransferFunction('vtkBlockColors')

# create a new 'Threshold'
threshold1 = Threshold(Input=advectionDiffusionModel_3D_meshConv_0_oute)
threshold1.Scalars = ['POINTS', 'ThermalDamage']

# Properties modified on threshold1
threshold1.ThresholdRange = [1.0, 1.0]

# show data in view
threshold1Display = Show(threshold1, renderView1)

# trace defaults for the display properties.
threshold1Display.Representation = 'Surface'
threshold1Display.ColorArrayName = [None, '']
threshold1Display.OSPRayScaleFunction = 'PiecewiseFunction'
threshold1Display.SelectOrientationVectors = 'None'
threshold1Display.ScaleFactor = -2.0000000000000002e+298
threshold1Display.SelectScaleArray = 'None'
threshold1Display.GlyphType = 'Arrow'
threshold1Display.GlyphTableIndexArray = 'None'
threshold1Display.GaussianRadius = -1e+297
threshold1Display.SetScaleArray = [None, '']
threshold1Display.ScaleTransferFunction = 'PiecewiseFunction'
threshold1Display.OpacityArray = [None, '']
threshold1Display.OpacityTransferFunction = 'PiecewiseFunction'
threshold1Display.DataAxesGrid = 'GridAxesRepresentation'
threshold1Display.SelectionCellLabelFontFile = ''
threshold1Display.SelectionPointLabelFontFile = ''
threshold1Display.PolarAxes = 'PolarAxesRepresentation'

# init the 'GridAxesRepresentation' selected for 'DataAxesGrid'
threshold1Display.DataAxesGrid.XTitleFontFile = ''
threshold1Display.DataAxesGrid.YTitleFontFile = ''
threshold1Display.DataAxesGrid.ZTitleFontFile = ''
threshold1Display.DataAxesGrid.XLabelFontFile = ''
threshold1Display.DataAxesGrid.YLabelFontFile = ''
threshold1Display.DataAxesGrid.ZLabelFontFile = ''

# init the 'PolarAxesRepresentation' selected for 'PolarAxes'
threshold1Display.PolarAxes.PolarAxisTitleFontFile = ''
threshold1Display.PolarAxes.PolarAxisLabelFontFile = ''
threshold1Display.PolarAxes.LastRadialAxisTextFontFile = ''
threshold1Display.PolarAxes.SecondaryRadialAxesTextFontFile = ''

# hide data in view
Hide(advectionDiffusionModel_3D_meshConv_0_oute, renderView1)

# update the view to ensure updated data information
renderView1.Update()

# set active source
SetActiveSource(advectionDiffusionModel_3D_meshConv_0_oute)

# set scalar coloring
ColorBy(advectionDiffusionModel_3D_meshConv_0_outeDisplay, ('POINTS', 'ThermalDamage'))

# Hide the scalar bar for this color map if no visible data is colored by it.
HideScalarBarIfNotNeeded(vtkBlockColorsLUT, renderView1)

# rescale color and/or opacity maps used to include current data range
advectionDiffusionModel_3D_meshConv_0_outeDisplay.RescaleTransferFunctionToDataRange(True, False)

# get color transfer function/color map for 'ThermalDamage'
thermalDamageLUT = GetColorTransferFunction('ThermalDamage')

# set active source
SetActiveSource(threshold1)

# reset view to fit data
renderView1.ResetCamera()

# reset view to fit data
renderView1.ResetCamera()

# hide data in view
Hide(threshold1, renderView1)

# set active source
SetActiveSource(threshold1)

# show data in view
threshold1Display = Show(threshold1, renderView1)

# reset view to fit data
renderView1.ResetCamera()

# Rescale transfer function
threshold1Display.ScaleTransferFunction.RescaleTransferFunction(1.0, 1.00024414062)

# Rescale transfer function
threshold1Display.OpacityTransferFunction.RescaleTransferFunction(1.0, 1.00024414062)

# Properties modified on threshold1Display
threshold1Display.SetScaleArray = [None, 'ThermalDamage']

# Properties modified on threshold1Display
threshold1Display.OpacityArray = [None, 'ThermalDamage']

# Properties modified on threshold1Display
threshold1Display.OSPRayScaleArray = 'ThermalDamage'

animationScene1.GoToLast()

# reset view to fit data
renderView1.ResetCamera()

# create a new 'ExodusIIReader'
advectionDiffusionModel_3D_meshConv_3_oute = ExodusIIReader(FileName=['/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/my_app/ModifiedPennesPerfusion/AdvectionDiffusionModel_3D_meshConv_3_out.e'])
advectionDiffusionModel_3D_meshConv_3_oute.PointVariables = []
advectionDiffusionModel_3D_meshConv_3_oute.GlobalVariables = []
advectionDiffusionModel_3D_meshConv_3_oute.NodeSetArrayStatus = []
advectionDiffusionModel_3D_meshConv_3_oute.SideSetArrayStatus = []

# Properties modified on advectionDiffusionModel_3D_meshConv_3_oute
advectionDiffusionModel_3D_meshConv_3_oute.GenerateObjectIdCellArray = 0
advectionDiffusionModel_3D_meshConv_3_oute.GenerateGlobalElementIdArray = 0
advectionDiffusionModel_3D_meshConv_3_oute.GenerateGlobalNodeIdArray = 0
advectionDiffusionModel_3D_meshConv_3_oute.PointVariables = ['ThermalDamage']
advectionDiffusionModel_3D_meshConv_3_oute.ElementBlocks = ['phantom', 'vessel', 'needle']

# show data in view
advectionDiffusionModel_3D_meshConv_3_outeDisplay = Show(advectionDiffusionModel_3D_meshConv_3_oute, renderView1)

# trace defaults for the display properties.
advectionDiffusionModel_3D_meshConv_3_outeDisplay.Representation = 'Surface'
advectionDiffusionModel_3D_meshConv_3_outeDisplay.ColorArrayName = [None, '']
advectionDiffusionModel_3D_meshConv_3_outeDisplay.OSPRayScaleArray = 'ThermalDamage'
advectionDiffusionModel_3D_meshConv_3_outeDisplay.OSPRayScaleFunction = 'PiecewiseFunction'
advectionDiffusionModel_3D_meshConv_3_outeDisplay.SelectOrientationVectors = 'None'
advectionDiffusionModel_3D_meshConv_3_outeDisplay.ScaleFactor = 0.010000000149011612
advectionDiffusionModel_3D_meshConv_3_outeDisplay.SelectScaleArray = 'None'
advectionDiffusionModel_3D_meshConv_3_outeDisplay.GlyphType = 'Arrow'
advectionDiffusionModel_3D_meshConv_3_outeDisplay.GlyphTableIndexArray = 'None'
advectionDiffusionModel_3D_meshConv_3_outeDisplay.GaussianRadius = 0.0005000000074505806
advectionDiffusionModel_3D_meshConv_3_outeDisplay.SetScaleArray = ['POINTS', 'ThermalDamage']
advectionDiffusionModel_3D_meshConv_3_outeDisplay.ScaleTransferFunction = 'PiecewiseFunction'
advectionDiffusionModel_3D_meshConv_3_outeDisplay.OpacityArray = ['POINTS', 'ThermalDamage']
advectionDiffusionModel_3D_meshConv_3_outeDisplay.OpacityTransferFunction = 'PiecewiseFunction'
advectionDiffusionModel_3D_meshConv_3_outeDisplay.DataAxesGrid = 'GridAxesRepresentation'
advectionDiffusionModel_3D_meshConv_3_outeDisplay.SelectionCellLabelFontFile = ''
advectionDiffusionModel_3D_meshConv_3_outeDisplay.SelectionPointLabelFontFile = ''
advectionDiffusionModel_3D_meshConv_3_outeDisplay.PolarAxes = 'PolarAxesRepresentation'
advectionDiffusionModel_3D_meshConv_3_outeDisplay.ScalarOpacityUnitDistance = 0.0016073412545274297

# init the 'GridAxesRepresentation' selected for 'DataAxesGrid'
advectionDiffusionModel_3D_meshConv_3_outeDisplay.DataAxesGrid.XTitleFontFile = ''
advectionDiffusionModel_3D_meshConv_3_outeDisplay.DataAxesGrid.YTitleFontFile = ''
advectionDiffusionModel_3D_meshConv_3_outeDisplay.DataAxesGrid.ZTitleFontFile = ''
advectionDiffusionModel_3D_meshConv_3_outeDisplay.DataAxesGrid.XLabelFontFile = ''
advectionDiffusionModel_3D_meshConv_3_outeDisplay.DataAxesGrid.YLabelFontFile = ''
advectionDiffusionModel_3D_meshConv_3_outeDisplay.DataAxesGrid.ZLabelFontFile = ''

# init the 'PolarAxesRepresentation' selected for 'PolarAxes'
advectionDiffusionModel_3D_meshConv_3_outeDisplay.PolarAxes.PolarAxisTitleFontFile = ''
advectionDiffusionModel_3D_meshConv_3_outeDisplay.PolarAxes.PolarAxisLabelFontFile = ''
advectionDiffusionModel_3D_meshConv_3_outeDisplay.PolarAxes.LastRadialAxisTextFontFile = ''
advectionDiffusionModel_3D_meshConv_3_outeDisplay.PolarAxes.SecondaryRadialAxesTextFontFile = ''

# update the view to ensure updated data information
renderView1.Update()

# set scalar coloring
ColorBy(advectionDiffusionModel_3D_meshConv_3_outeDisplay, ('FIELD', 'vtkBlockColors'))

# show color bar/color legend
advectionDiffusionModel_3D_meshConv_3_outeDisplay.SetScalarBarVisibility(renderView1, True)

# hide data in view
Hide(threshold1, renderView1)

# create a new 'Threshold'
threshold2 = Threshold(Input=advectionDiffusionModel_3D_meshConv_3_oute)
threshold2.Scalars = ['POINTS', 'ThermalDamage']
threshold2.ThresholdRange = [0.0, 1.0]

# Properties modified on threshold2
threshold2.ThresholdRange = [1.0, 1.0]

# show data in view
threshold2Display = Show(threshold2, renderView1)

# trace defaults for the display properties.
threshold2Display.Representation = 'Surface'
threshold2Display.ColorArrayName = [None, '']
threshold2Display.OSPRayScaleArray = 'ThermalDamage'
threshold2Display.OSPRayScaleFunction = 'PiecewiseFunction'
threshold2Display.SelectOrientationVectors = 'None'
threshold2Display.ScaleFactor = 0.003881293907761574
threshold2Display.SelectScaleArray = 'None'
threshold2Display.GlyphType = 'Arrow'
threshold2Display.GlyphTableIndexArray = 'None'
threshold2Display.GaussianRadius = 0.0001940646953880787
threshold2Display.SetScaleArray = ['POINTS', 'ThermalDamage']
threshold2Display.ScaleTransferFunction = 'PiecewiseFunction'
threshold2Display.OpacityArray = ['POINTS', 'ThermalDamage']
threshold2Display.OpacityTransferFunction = 'PiecewiseFunction'
threshold2Display.DataAxesGrid = 'GridAxesRepresentation'
threshold2Display.SelectionCellLabelFontFile = ''
threshold2Display.SelectionPointLabelFontFile = ''
threshold2Display.PolarAxes = 'PolarAxesRepresentation'
threshold2Display.ScalarOpacityUnitDistance = 0.0007347734156525779

# init the 'PiecewiseFunction' selected for 'ScaleTransferFunction'
threshold2Display.ScaleTransferFunction.Points = [1.0, 0.0, 0.5, 0.0, 1.000244140625, 1.0, 0.5, 0.0]

# init the 'PiecewiseFunction' selected for 'OpacityTransferFunction'
threshold2Display.OpacityTransferFunction.Points = [1.0, 0.0, 0.5, 0.0, 1.000244140625, 1.0, 0.5, 0.0]

# init the 'GridAxesRepresentation' selected for 'DataAxesGrid'
threshold2Display.DataAxesGrid.XTitleFontFile = ''
threshold2Display.DataAxesGrid.YTitleFontFile = ''
threshold2Display.DataAxesGrid.ZTitleFontFile = ''
threshold2Display.DataAxesGrid.XLabelFontFile = ''
threshold2Display.DataAxesGrid.YLabelFontFile = ''
threshold2Display.DataAxesGrid.ZLabelFontFile = ''

# init the 'PolarAxesRepresentation' selected for 'PolarAxes'
threshold2Display.PolarAxes.PolarAxisTitleFontFile = ''
threshold2Display.PolarAxes.PolarAxisLabelFontFile = ''
threshold2Display.PolarAxes.LastRadialAxisTextFontFile = ''
threshold2Display.PolarAxes.SecondaryRadialAxesTextFontFile = ''

# hide data in view
Hide(advectionDiffusionModel_3D_meshConv_3_oute, renderView1)

# update the view to ensure updated data information
renderView1.Update()

# set scalar coloring
ColorBy(threshold2Display, ('FIELD', 'vtkBlockColors'))

# show color bar/color legend
threshold2Display.SetScalarBarVisibility(renderView1, True)

# set active source
SetActiveSource(threshold1)

# create a new 'Group Datasets'
groupDatasets1 = GroupDatasets(Input=[threshold2, threshold1])

# hide data in view
Hide(threshold2, renderView1)

# set active source
SetActiveSource(groupDatasets1)

# show data in view
groupDatasets1Display = Show(groupDatasets1, renderView1)

# trace defaults for the display properties.
groupDatasets1Display.Representation = 'Surface'
groupDatasets1Display.ColorArrayName = [None, '']
groupDatasets1Display.OSPRayScaleArray = 'ThermalDamage'
groupDatasets1Display.OSPRayScaleFunction = 'PiecewiseFunction'
groupDatasets1Display.SelectOrientationVectors = 'None'
groupDatasets1Display.ScaleFactor = 0.003881293907761574
groupDatasets1Display.SelectScaleArray = 'None'
groupDatasets1Display.GlyphType = 'Arrow'
groupDatasets1Display.GlyphTableIndexArray = 'None'
groupDatasets1Display.GaussianRadius = 0.0001940646953880787
groupDatasets1Display.SetScaleArray = ['POINTS', 'ThermalDamage']
groupDatasets1Display.ScaleTransferFunction = 'PiecewiseFunction'
groupDatasets1Display.OpacityArray = ['POINTS', 'ThermalDamage']
groupDatasets1Display.OpacityTransferFunction = 'PiecewiseFunction'
groupDatasets1Display.DataAxesGrid = 'GridAxesRepresentation'
groupDatasets1Display.SelectionCellLabelFontFile = ''
groupDatasets1Display.SelectionPointLabelFontFile = ''
groupDatasets1Display.PolarAxes = 'PolarAxesRepresentation'
groupDatasets1Display.ScalarOpacityUnitDistance = 0.0007214333471393346

# init the 'PiecewiseFunction' selected for 'ScaleTransferFunction'
groupDatasets1Display.ScaleTransferFunction.Points = [1.0, 0.0, 0.5, 0.0, 1.000244140625, 1.0, 0.5, 0.0]

# init the 'PiecewiseFunction' selected for 'OpacityTransferFunction'
groupDatasets1Display.OpacityTransferFunction.Points = [1.0, 0.0, 0.5, 0.0, 1.000244140625, 1.0, 0.5, 0.0]

# init the 'GridAxesRepresentation' selected for 'DataAxesGrid'
groupDatasets1Display.DataAxesGrid.XTitleFontFile = ''
groupDatasets1Display.DataAxesGrid.YTitleFontFile = ''
groupDatasets1Display.DataAxesGrid.ZTitleFontFile = ''
groupDatasets1Display.DataAxesGrid.XLabelFontFile = ''
groupDatasets1Display.DataAxesGrid.YLabelFontFile = ''
groupDatasets1Display.DataAxesGrid.ZLabelFontFile = ''

# init the 'PolarAxesRepresentation' selected for 'PolarAxes'
groupDatasets1Display.PolarAxes.PolarAxisTitleFontFile = ''
groupDatasets1Display.PolarAxes.PolarAxisLabelFontFile = ''
groupDatasets1Display.PolarAxes.LastRadialAxisTextFontFile = ''
groupDatasets1Display.PolarAxes.SecondaryRadialAxesTextFontFile = ''

# reset view to fit data
renderView1.ResetCamera()

# set active source
SetActiveSource(groupDatasets1)

#### saving camera placements for all active views

# current camera placement for renderView1
renderView1.CameraPosition = [-0.07923526207377286, 0.0342031484545092, -0.07484135800267516]
renderView1.CameraFocalPoint = [5.526328459382057e-05, -0.0005506309680640697, -0.054184501990675926]
renderView1.CameraViewUp = [-0.3175096989448067, -0.16989517584059927, 0.9329111534878711]
renderView1.CameraParallelScale = 0.023035648624780507

#### uncomment the following to render all views
# RenderAllViews()
# alternatively, if you want to write images, you can use SaveScreenshot(...).
