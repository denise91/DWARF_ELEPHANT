# trace generated using paraview version 5.5.2

#### import the simple module from the paraview
from paraview.simple import *
import numpy as np

float_formatter = "{:.3e}".format
r_ref_arr = [np.longdouble(float_formatter(4e-4)),np.longdouble(float_formatter(1.414e-3)),np.longdouble(float_formatter(5e-3))]
l_ref_arr = [np.longdouble(float_formatter(5e-3)),np.longdouble(float_formatter(1.871e-2)),np.longdouble(float_formatter(7e-2))]

deformed_mesh_names = {'min_min':["Min","Max"],'max_min':["Min","Max"],'min_max':["Min","Max"],'max_max':["Min","Max"]}
param_values_dict = {
  'min_min':{'Min':{'r':r_ref_arr[0],'l':l_ref_arr[0]},'Max':{'r':r_ref_arr[1],'l':l_ref_arr[1]}},
  'min_max':{'Min':{'r':r_ref_arr[0],'l':l_ref_arr[1]},'Max':{'r':r_ref_arr[1],'l':l_ref_arr[2]}},
  'max_min':{'Min':{'r':r_ref_arr[1],'l':l_ref_arr[0]},'Max':{'r':r_ref_arr[2],'l':l_ref_arr[1]}},
  'max_max':{'Min':{'r':r_ref_arr[1],'l':l_ref_arr[1]},'Max':{'r':r_ref_arr[2],'l':l_ref_arr[2]}}
}

for i, param_subd in enumerate(list(param_values_dict)):
  for j, mesh_name in enumerate(deformed_mesh_names[param_subd]):
    filename_matlab = '/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/PDSplit/'+param_subd+'/param'+mesh_name+'/mesh2/Arrh_tissue_damage.e'
    filename_moose = '/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/my_app/2DGeomParaTest/3DRBRFA_Perf_Transient_r{r:.3e}mm_l{l:.3e}mm_out.e'.format(r=param_values_dict[param_subd][mesh_name]['r'],l=param_values_dict[param_subd][mesh_name]['l'])
    filename_screenshot_with_mesh_1 = '/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/PDSplit/'+param_subd+'_param'+mesh_name+'_damage_with_mesh_compare_1.png'
    filename_screenshot_with_mesh_2 = '/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/PDSplit/'+param_subd+'_param'+mesh_name+'_damage_with_mesh_compare_2.png'
    filename_screenshot = '/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/PDSplit/'+param_subd+'_param'+mesh_name+'_damage_compare.png'
    print(filename_matlab)
    print(filename_moose)
    print(filename_screenshot)
    print(filename_screenshot_with_mesh_1)
    print(filename_screenshot_with_mesh_2)

    #### disable automatic camera reset on 'Show'
    paraview.simple._DisableFirstRenderCameraReset()
    
    # create a new 'ExodusIIReader'
    #arrh_tissue_damagee = ExodusIIReader(FileName=['/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/PDSplit/min_min/paramMin/mesh2/Arrh_tissue_damage.e'])
    arrh_tissue_damagee = ExodusIIReader(FileName=[filename_matlab])
    print('First file loaded.')
    arrh_tissue_damagee.ElementVariables = []
    arrh_tissue_damagee.PointVariables = []
    
    # Properties modified on arrh_tissue_damagee
    arrh_tissue_damagee.GenerateObjectIdCellArray = 0
    arrh_tissue_damagee.GenerateGlobalElementIdArray = 0
    arrh_tissue_damagee.GenerateGlobalNodeIdArray = 0
    arrh_tissue_damagee.PointVariables = ['arrhenius_tissue_damage']
    arrh_tissue_damagee.ElementBlocks = ['Unnamed block ID: 10 Type: TETRA']
    
    # get active view
    renderView1 = GetActiveViewOrCreate('RenderView')
    # uncomment following to set a specific view size
    # renderView1.ViewSize = [1277, 519]
    
    # show data in view
    arrh_tissue_damageeDisplay = Show(arrh_tissue_damagee, renderView1)
    
    # trace defaults for the display properties.
    arrh_tissue_damageeDisplay.Representation = 'Surface'
    arrh_tissue_damageeDisplay.ColorArrayName = [None, '']
    arrh_tissue_damageeDisplay.OSPRayScaleArray = 'arrhenius_tissue_damage'
    arrh_tissue_damageeDisplay.OSPRayScaleFunction = 'PiecewiseFunction'
    arrh_tissue_damageeDisplay.SelectOrientationVectors = 'None'
    arrh_tissue_damageeDisplay.ScaleFactor = 0.010000000149011612
    arrh_tissue_damageeDisplay.SelectScaleArray = 'None'
    arrh_tissue_damageeDisplay.GlyphType = 'Arrow'
    arrh_tissue_damageeDisplay.GlyphTableIndexArray = 'None'
    arrh_tissue_damageeDisplay.GaussianRadius = 0.0005000000074505806
    arrh_tissue_damageeDisplay.SetScaleArray = ['POINTS', 'arrhenius_tissue_damage']
    arrh_tissue_damageeDisplay.ScaleTransferFunction = 'PiecewiseFunction'
    arrh_tissue_damageeDisplay.OpacityArray = ['POINTS', 'arrhenius_tissue_damage']
    arrh_tissue_damageeDisplay.OpacityTransferFunction = 'PiecewiseFunction'
    arrh_tissue_damageeDisplay.DataAxesGrid = 'GridAxesRepresentation'
    arrh_tissue_damageeDisplay.SelectionCellLabelFontFile = ''
    arrh_tissue_damageeDisplay.SelectionPointLabelFontFile = ''
    arrh_tissue_damageeDisplay.PolarAxes = 'PolarAxesRepresentation'
    arrh_tissue_damageeDisplay.ScalarOpacityUnitDistance = 0.0015003986224110108
    
    # init the 'GridAxesRepresentation' selected for 'DataAxesGrid'
    arrh_tissue_damageeDisplay.DataAxesGrid.XTitleFontFile = ''
    arrh_tissue_damageeDisplay.DataAxesGrid.YTitleFontFile = ''
    arrh_tissue_damageeDisplay.DataAxesGrid.ZTitleFontFile = ''
    arrh_tissue_damageeDisplay.DataAxesGrid.XLabelFontFile = ''
    arrh_tissue_damageeDisplay.DataAxesGrid.YLabelFontFile = ''
    arrh_tissue_damageeDisplay.DataAxesGrid.ZLabelFontFile = ''
    
    # init the 'PolarAxesRepresentation' selected for 'PolarAxes'
    arrh_tissue_damageeDisplay.PolarAxes.PolarAxisTitleFontFile = ''
    arrh_tissue_damageeDisplay.PolarAxes.PolarAxisLabelFontFile = ''
    arrh_tissue_damageeDisplay.PolarAxes.LastRadialAxisTextFontFile = ''
    arrh_tissue_damageeDisplay.PolarAxes.SecondaryRadialAxesTextFontFile = ''
    
    # reset view to fit data
    renderView1.ResetCamera()
    
    # update the view to ensure updated data information
    renderView1.Update()
    
    # create a new 'Clip'
    clip1 = Clip(Input=arrh_tissue_damagee)
    clip1.ClipType = 'Plane'
    clip1.Scalars = ['POINTS', 'arrhenius_tissue_damage']
    clip1.Value = 0.5
    
    # Properties modified on clip1.ClipType
    clip1.ClipType.Normal = [0.0, 0.0, 1.0]
    
    # Properties modified on clip1.ClipType
    clip1.ClipType.Normal = [0.0, 0.0, 1.0]
    
    # show data in view
    clip1Display = Show(clip1, renderView1)
    
    # trace defaults for the display properties.
    clip1Display.Representation = 'Surface'
    clip1Display.ColorArrayName = [None, '']
    clip1Display.OSPRayScaleArray = 'arrhenius_tissue_damage'
    clip1Display.OSPRayScaleFunction = 'PiecewiseFunction'
    clip1Display.SelectOrientationVectors = 'None'
    clip1Display.ScaleFactor = 0.010000000149011612
    clip1Display.SelectScaleArray = 'None'
    clip1Display.GlyphType = 'Arrow'
    clip1Display.GlyphTableIndexArray = 'None'
    clip1Display.GaussianRadius = 0.0005000000074505806
    clip1Display.SetScaleArray = ['POINTS', 'arrhenius_tissue_damage']
    clip1Display.ScaleTransferFunction = 'PiecewiseFunction'
    clip1Display.OpacityArray = ['POINTS', 'arrhenius_tissue_damage']
    clip1Display.OpacityTransferFunction = 'PiecewiseFunction'
    clip1Display.DataAxesGrid = 'GridAxesRepresentation'
    clip1Display.SelectionCellLabelFontFile = ''
    clip1Display.SelectionPointLabelFontFile = ''
    clip1Display.PolarAxes = 'PolarAxesRepresentation'
    clip1Display.ScalarOpacityUnitDistance = 0.0016246139141699034
    
    # init the 'GridAxesRepresentation' selected for 'DataAxesGrid'
    clip1Display.DataAxesGrid.XTitleFontFile = ''
    clip1Display.DataAxesGrid.YTitleFontFile = ''
    clip1Display.DataAxesGrid.ZTitleFontFile = ''
    clip1Display.DataAxesGrid.XLabelFontFile = ''
    clip1Display.DataAxesGrid.YLabelFontFile = ''
    clip1Display.DataAxesGrid.ZLabelFontFile = ''
    
    # init the 'PolarAxesRepresentation' selected for 'PolarAxes'
    clip1Display.PolarAxes.PolarAxisTitleFontFile = ''
    clip1Display.PolarAxes.PolarAxisLabelFontFile = ''
    clip1Display.PolarAxes.LastRadialAxisTextFontFile = ''
    clip1Display.PolarAxes.SecondaryRadialAxesTextFontFile = ''
    
    # hide data in view
    Hide(arrh_tissue_damagee, renderView1)
    
    # update the view to ensure updated data information
    renderView1.Update()
    
    # toggle 3D widget visibility (only when running from the GUI)
    Hide3DWidgets(proxy=clip1.ClipType)
    
    # set scalar coloring
    ColorBy(clip1Display, ('POINTS', 'arrhenius_tissue_damage'))
    
    # rescale color and/or opacity maps used to include current data range
    clip1Display.RescaleTransferFunctionToDataRange(True, False)
    
    # show color bar/color legend
    clip1Display.SetScalarBarVisibility(renderView1, True)
    
    # get color transfer function/color map for 'arrhenius_tissue_damage'
    arrhenius_tissue_damageLUT = GetColorTransferFunction('arrhenius_tissue_damage')
    
    # change representation type
    clip1Display.SetRepresentationType('Surface With Edges')
    
    # get layout
    layout1 = GetLayout()
    
    # split cell
    layout1.SplitHorizontal(0, 0.5)
    
    # set active view
    SetActiveView(None)
    
    # create a new 'ExodusIIReader'
    #a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_oute = ExodusIIReader(FileName=['/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/my_app/2DGeomParaTest/3DRBRFA_Perf_Transient_r4.000e-04mm_l5.000e-03mm_out.e'])
    a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_oute = ExodusIIReader(FileName=[filename_moose])
    print('Load second file.')
    a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_oute.PointVariables = []
    a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_oute.NodeSetArrayStatus = []
    a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_oute.SideSetArrayStatus = []
    
    # Properties modified on a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_oute
    a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_oute.GenerateObjectIdCellArray = 0
    a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_oute.GenerateGlobalElementIdArray = 0
    a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_oute.GenerateGlobalNodeIdArray = 0
    a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_oute.PointVariables = ['ThermalDamage']
    a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_oute.ElementBlocks = ['maxZ1', 'maxZ2', 'maxZ3', 'maxZ4', 'maxZ5', 'minX1', 'minX2', 'minX3', 'minX4', 'minX5', 'maxY1', 'maxY2', 'maxY3', 'maxY4', 'maxY5', 'maxX1', 'maxX2', 'maxX3', 'maxX4', 'maxX5', 'minY1', 'minY2', 'minY3', 'minY4', 'minY5', 'minZ1', 'minZ2', 'minZ3', 'minZ4', 'minZ5', 'cylinder', 'bounding']
    
    # get the material library
    materialLibrary1 = GetMaterialLibrary()
    
    # Create a new 'Render View'
    renderView2 = CreateView('RenderView')
    renderView2.ViewSize = [634, 519]
    renderView2.AxesGrid = 'GridAxes3DActor'
    renderView2.StereoType = 0
    renderView2.Background = [0.32, 0.34, 0.43]
    renderView2.OSPRayMaterialLibrary = materialLibrary1
    
    # init the 'GridAxes3DActor' selected for 'AxesGrid'
    renderView2.AxesGrid.XTitleFontFile = ''
    renderView2.AxesGrid.YTitleFontFile = ''
    renderView2.AxesGrid.ZTitleFontFile = ''
    renderView2.AxesGrid.XLabelFontFile = ''
    renderView2.AxesGrid.YLabelFontFile = ''
    renderView2.AxesGrid.ZLabelFontFile = ''
    
    # place view in the layout
    layout1.AssignView(2, renderView2)
    
    # show data in view
    a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_outeDisplay = Show(a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_oute, renderView2)
    
    # trace defaults for the display properties.
    a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_outeDisplay.Representation = 'Surface'
    a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_outeDisplay.ColorArrayName = [None, '']
    a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_outeDisplay.OSPRayScaleArray = 'ThermalDamage'
    a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_outeDisplay.OSPRayScaleFunction = 'PiecewiseFunction'
    a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_outeDisplay.SelectOrientationVectors = 'None'
    a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_outeDisplay.ScaleFactor = 0.010000000149011612
    a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_outeDisplay.SelectScaleArray = 'None'
    a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_outeDisplay.GlyphType = 'Arrow'
    a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_outeDisplay.GlyphTableIndexArray = 'None'
    a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_outeDisplay.GaussianRadius = 0.0005000000074505806
    a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_outeDisplay.SetScaleArray = ['POINTS', 'ThermalDamage']
    a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_outeDisplay.ScaleTransferFunction = 'PiecewiseFunction'
    a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_outeDisplay.OpacityArray = ['POINTS', 'ThermalDamage']
    a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_outeDisplay.OpacityTransferFunction = 'PiecewiseFunction'
    a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_outeDisplay.DataAxesGrid = 'GridAxesRepresentation'
    a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_outeDisplay.SelectionCellLabelFontFile = ''
    a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_outeDisplay.SelectionPointLabelFontFile = ''
    a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_outeDisplay.PolarAxes = 'PolarAxesRepresentation'
    a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_outeDisplay.ScalarOpacityUnitDistance = 0.001621905118514006
    
    # init the 'GridAxesRepresentation' selected for 'DataAxesGrid'
    a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_outeDisplay.DataAxesGrid.XTitleFontFile = ''
    a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_outeDisplay.DataAxesGrid.YTitleFontFile = ''
    a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_outeDisplay.DataAxesGrid.ZTitleFontFile = ''
    a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_outeDisplay.DataAxesGrid.XLabelFontFile = ''
    a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_outeDisplay.DataAxesGrid.YLabelFontFile = ''
    a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_outeDisplay.DataAxesGrid.ZLabelFontFile = ''
    
    # init the 'PolarAxesRepresentation' selected for 'PolarAxes'
    a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_outeDisplay.PolarAxes.PolarAxisTitleFontFile = ''
    a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_outeDisplay.PolarAxes.PolarAxisLabelFontFile = ''
    a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_outeDisplay.PolarAxes.LastRadialAxisTextFontFile = ''
    a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_outeDisplay.PolarAxes.SecondaryRadialAxesTextFontFile = ''
    
    # reset view to fit data
    renderView2.ResetCamera()
    
    # update the view to ensure updated data information
    renderView2.Update()
    
    # set scalar coloring
    ColorBy(a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_outeDisplay, ('FIELD', 'vtkBlockColors'))
    
    # show color bar/color legend
    a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_outeDisplay.SetScalarBarVisibility(renderView2, True)
    
    # get color transfer function/color map for 'vtkBlockColors'
    vtkBlockColorsLUT = GetColorTransferFunction('vtkBlockColors')
    
    # create a new 'Clip'
    clip2 = Clip(Input=a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_oute)
    clip2.ClipType = 'Plane'
    clip2.Scalars = ['POINTS', 'ThermalDamage']
    clip2.Value = 0.5
    
    # Properties modified on clip2.ClipType
    clip2.ClipType.Normal = [0.0, 0.0, 1.0]
    
    # Properties modified on clip2.ClipType
    clip2.ClipType.Normal = [0.0, 0.0, 1.0]
    
    # show data in view
    clip2Display = Show(clip2, renderView2)
    
    # trace defaults for the display properties.
    clip2Display.Representation = 'Surface'
    clip2Display.ColorArrayName = [None, '']
    clip2Display.OSPRayScaleArray = 'ThermalDamage'
    clip2Display.OSPRayScaleFunction = 'PiecewiseFunction'
    clip2Display.SelectOrientationVectors = 'None'
    clip2Display.ScaleFactor = 0.010000000149011612
    clip2Display.SelectScaleArray = 'None'
    clip2Display.GlyphType = 'Arrow'
    clip2Display.GlyphTableIndexArray = 'None'
    clip2Display.GaussianRadius = 0.0005000000074505806
    clip2Display.SetScaleArray = ['POINTS', 'ThermalDamage']
    clip2Display.ScaleTransferFunction = 'PiecewiseFunction'
    clip2Display.OpacityArray = ['POINTS', 'ThermalDamage']
    clip2Display.OpacityTransferFunction = 'PiecewiseFunction'
    clip2Display.DataAxesGrid = 'GridAxesRepresentation'
    clip2Display.SelectionCellLabelFontFile = ''
    clip2Display.SelectionPointLabelFontFile = ''
    clip2Display.PolarAxes = 'PolarAxesRepresentation'
    clip2Display.ScalarOpacityUnitDistance = 0.0017530438932508864
    
    # init the 'GridAxesRepresentation' selected for 'DataAxesGrid'
    clip2Display.DataAxesGrid.XTitleFontFile = ''
    clip2Display.DataAxesGrid.YTitleFontFile = ''
    clip2Display.DataAxesGrid.ZTitleFontFile = ''
    clip2Display.DataAxesGrid.XLabelFontFile = ''
    clip2Display.DataAxesGrid.YLabelFontFile = ''
    clip2Display.DataAxesGrid.ZLabelFontFile = ''
    
    # init the 'PolarAxesRepresentation' selected for 'PolarAxes'
    clip2Display.PolarAxes.PolarAxisTitleFontFile = ''
    clip2Display.PolarAxes.PolarAxisLabelFontFile = ''
    clip2Display.PolarAxes.LastRadialAxisTextFontFile = ''
    clip2Display.PolarAxes.SecondaryRadialAxesTextFontFile = ''
    
    # hide data in view
    Hide(a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_oute, renderView2)
    
    # update the view to ensure updated data information
    renderView2.Update()
    
    # set scalar coloring
    ColorBy(clip2Display, ('FIELD', 'vtkBlockColors'))
    
    # show color bar/color legend
    clip2Display.SetScalarBarVisibility(renderView2, True)
    
    # toggle 3D widget visibility (only when running from the GUI)
    Hide3DWidgets(proxy=clip2.ClipType)
    
    # change representation type
    clip2Display.SetRepresentationType('Surface With Edges')
    
    # set scalar coloring
    ColorBy(clip2Display, ('POINTS', 'ThermalDamage'))
    
    # Hide the scalar bar for this color map if no visible data is colored by it.
    HideScalarBarIfNotNeeded(vtkBlockColorsLUT, renderView2)
    
    # rescale color and/or opacity maps used to include current data range
    clip2Display.RescaleTransferFunctionToDataRange(True, False)
    
    # show color bar/color legend
    clip2Display.SetScalarBarVisibility(renderView2, True)
    
    # get color transfer function/color map for 'ThermalDamage'
    thermalDamageLUT = GetColorTransferFunction('ThermalDamage')
    
    # reset view to fit data
    renderView2.ResetCamera()
    
    # set active view
    SetActiveView(renderView1)
    
    # reset view to fit data
    renderView1.ResetCamera()
    
    # set active source
    SetActiveSource(clip1)
    
    # change representation type
    clip1Display.SetRepresentationType('Surface')
    
    # set active view
    SetActiveView(renderView2)
    
    # set active source
    SetActiveSource(clip2)
    
    # change representation type
    clip2Display.SetRepresentationType('Surface')
    
    # current camera placement for renderView2
    renderView2.CameraPosition = [0.0, 0.0, 0.2647777518322164]
    renderView2.CameraFocalPoint = [0.0, 0.0, -0.02500000037252903]
    renderView2.CameraParallelScale = 0.07500000111758709
    
    # save screenshot
    #SaveScreenshot('/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/PDSplit/min_min_paramMin_damage_compare.png', renderView2, ImageResolution=[1268, 1038])
    
    # set active view
    SetActiveView(renderView1)
    
    # set active view
    SetActiveView(renderView2)
    
    # change representation type
    clip2Display.SetRepresentationType('Surface With Edges')
    
    # set active view
    SetActiveView(renderView1)
    
    # set active source
    SetActiveSource(clip1)
    
    # change representation type
    clip1Display.SetRepresentationType('Surface With Edges')
    
    # current camera placement for renderView1
    renderView1.CameraPosition = [-0.0092993159013358, 9.207243466669175e-05, 0.0641691312050855]
    renderView1.CameraFocalPoint = [-0.0092993159013358, 9.207243466669186e-05, -0.028162990934181602]
    renderView1.CameraViewUp = [0.0, 1.0, 1.1888067405718913e-18]
    renderView1.CameraParallelScale = 0.07500000111758709
    
    # save screenshot
    #SaveScreenshot('/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/PDSplit/min_min_paramMin_damage_with_mesh_compare_1.png', renderView1, ImageResolution=[1268, 1038])
    
    # set active view
    SetActiveView(renderView2)
    
    # set active source
    SetActiveSource(clip2)
    
    # current camera placement for renderView2
    renderView2.CameraPosition = [-0.0014644636742687962, -0.00018044416453563906, 0.017421551454820924]
    renderView2.CameraFocalPoint = [-0.0014644636742687962, -0.00018044416453563895, -0.07491057068444616]
    renderView2.CameraViewUp = [0.0, 1.0, 1.1888067405718913e-18]
    renderView2.CameraParallelScale = 0.07500000111758709
    
    # save screenshot
    #SaveScreenshot('/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/PDSplit/min_min_paramMin_damage_with_mesh_compare_2.png', renderView2, ImageResolution=[1268, 1038])
    
    # current camera placement for renderView2
    renderView2.CameraPosition = [-0.0014644636742687962, -0.00018044416453563906, 0.017421551454820924]
    renderView2.CameraFocalPoint = [-0.0014644636742687962, -0.00018044416453563895, -0.07491057068444616]
    renderView2.CameraViewUp = [0.0, 1.0, 1.1888067405718913e-18]
    renderView2.CameraParallelScale = 0.07500000111758709
    
    # current camera placement for renderView1
    renderView1.CameraPosition = [-0.0014644636742687962, -0.00018044416453563906, 0.017421551454820924]
    renderView1.CameraFocalPoint = [-0.0014644636742687962, -0.00018044416453563895, -0.07491057068444616]
    renderView1.CameraViewUp = [0.0, 1.0, 1.1888067405718913e-18]
    renderView1.CameraParallelScale = 0.07500000111758709
    
    # save screenshot
    #SaveScreenshot('/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/PDSplit/min_min_paramMin_damage_with_mesh_compare_2.png', layout1, SaveAllViews=1,
    #    ImageResolution=[2536, 1038])
    SaveScreenshot(filename_screenshot_with_mesh_2, layout1, SaveAllViews=1,
        ImageResolution=[2536, 1038])
    
    # current camera placement for renderView2
    renderView2.CameraPosition = [-0.012568755095110476, -0.000996936180773999, 0.05407457204601587]
    renderView2.CameraFocalPoint = [-0.012568755095110476, -0.000996936180773999, -0.03825755009325123]
    renderView2.CameraViewUp = [0.0, 1.0, 1.1888067405718913e-18]
    renderView2.CameraParallelScale = 0.07500000111758709
    
    # current camera placement for renderView1
    renderView1.CameraPosition = [-0.012568755095110476, -0.000996936180773999, 0.05407457204601587]
    renderView1.CameraFocalPoint = [-0.012568755095110476, -0.000996936180773999, -0.03825755009325123]
    renderView1.CameraViewUp = [0.0, 1.0, 1.1888067405718913e-18]
    renderView1.CameraParallelScale = 0.07500000111758709
    
    # save screenshot
    #SaveScreenshot('/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/PDSplit/min_min_paramMin_damage_with_mesh_compare_1.png', layout1, SaveAllViews=1,
    #    ImageResolution=[2536, 1038])
    SaveScreenshot(filename_screenshot_with_mesh_1, layout1, SaveAllViews=1,
        ImageResolution=[2536, 1038])
    
    # change representation type
    clip2Display.SetRepresentationType('Surface')
    
    # set active view
    SetActiveView(renderView1)
    
    # set active source
    SetActiveSource(clip1)
    
    # change representation type
    clip1Display.SetRepresentationType('Surface')
    
    # reset view to fit data
    renderView1.ResetCamera()
    
    # current camera placement for renderView2
    renderView2.CameraPosition = [0.0, 0.0, 0.19054087842669012]
    renderView2.CameraFocalPoint = [0.0, 0.0, -0.09923687377805546]
    renderView2.CameraViewUp = [0.0, 1.0, 1.1888067405718913e-18]
    renderView2.CameraParallelScale = 0.07500000111758709
    
    # current camera placement for renderView1
    renderView1.CameraPosition = [0.0, 0.0, 0.19054087842669012]
    renderView1.CameraFocalPoint = [0.0, 0.0, -0.09923687377805546]
    renderView1.CameraViewUp = [0.0, 1.0, 1.1888067405718913e-18]
    renderView1.CameraParallelScale = 0.07500000111758709
    
    # save screenshot
    #SaveScreenshot('/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/PDSplit/min_min_paramMin_damage_compare.png', layout1, SaveAllViews=1,
    #    ImageResolution=[2536, 1038])
    SaveScreenshot(filename_screenshot, layout1, SaveAllViews=1,
        ImageResolution=[2536, 1038])
    #### saving camera placements for all active views
    
    # current camera placement for renderView2
    renderView2.CameraPosition = [0.0, 0.0, 0.19054087842669012]
    renderView2.CameraFocalPoint = [0.0, 0.0, -0.09923687377805546]
    renderView2.CameraViewUp = [0.0, 1.0, 1.1888067405718913e-18]
    renderView2.CameraParallelScale = 0.07500000111758709
    
    # current camera placement for renderView1
    renderView1.CameraPosition = [0.0, 0.0, 0.19054087842669012]
    renderView1.CameraFocalPoint = [0.0, 0.0, -0.09923687377805546]
    renderView1.CameraViewUp = [0.0, 1.0, 1.1888067405718913e-18]
    renderView1.CameraParallelScale = 0.07500000111758709
    
    #### uncomment the following to render all views
    # RenderAllViews()
    # alternatively, if you want to write images, you can use SaveScreenshot(...).
    
    # destroy clip1
    Delete(clip1)
    del clip1
    
    # destroy ExodusIIReader
    Delete(arrh_tissue_damagee)
    del arrh_tissue_damagee

    # destroy clip2
    Delete(clip2)
    del clip2

    # destroy ExodusIIReader
    Delete(a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_oute)
    del a3DRBRFA_Perf_Transient_r4000e04mm_l5000e03mm_oute

    # set active view
    SetActiveView(renderView1)
    
    # destroy renderView1
    Delete(renderView1)
    del renderView1

    # set active view
    SetActiveView(renderView2)
    
    # destroy renderView2
    Delete(renderView2)
    del renderView2
