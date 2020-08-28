function write_vtu ( output_unit, node_num, element_num, ...
  element_order, xyz, element_node, p, data_name )

%*****************************************************************************80
%
%% VTU_PUVW_WRITE writes pressure and velocity data to a VTU file.
%
%  Discussion:
%
%    The data is assumed to have been computed by a finite element program
%    for a 3D geometry which has been meshed using tetrahedral elements 
%    of 4 or 10 nodes.
%
%    The solution data includes the pressure and velocity vector at each node.
%
%    The VTU format used here is the modern XML-based format used by the
%    Visual Toolkit for unstructured grid data.
%
%  Licensing:
%
%    This code is distributed under the GNU LGPL license.
%
%  Modified:
%
%    20 December 2010
%
%  Author:
%
%    John Burkardt
%
%  Parameters:
%
%    Input, integer OUTPUT_UNIT, the output unit.
%
%    Input, string TITLE, a title for the data.
%
%    Input, integer NODE_NUM, the number of nodes.
%
%    Input, integer ELEMENT_NUM, the number of elements.
%
%    Input, integer ELEMENT_ORDER, the order of the elements (number of nodes per element).
%
%    Input, real XYZ(3,NODE_NUM), the node coordinates.
%
%    Input, integer ELEMENT_NODE(ELEMENT_ORDER,ELEMENT_NUM), the
%    nodes that make up each element.  The node indices are zero based.
%
%    Input, real P(1,NODE_NUM), the solution at each node.
%
  if ( element_order == 10 )
    fprintf ( 1, '\n' );
    fprintf ( 1, 'VTU_PUVW_WRITE - Note:\n' );
    fprintf ( 1, '  As a temporary measure, we are handling quadratic tets\n' );
    fprintf ( 1, '  as though they were linear.  That is, the element information\n' );
    fprintf ( 1, '  will only use the vertices, not the midside nodes.\n' );
    element_order = 4;
  end

  fprintf ( output_unit, '<?xml version="1.0"?>\n' );
  fprintf ( output_unit, '<VTKFile type="UnstructuredGrid" version="0.1" byte_order="BigEndian"  header_type="UInt32" compressor="vtkZLibDataCompressor">\n' );
  fprintf ( output_unit, '  <UnstructuredGrid>\n' );
  fprintf ( output_unit, '    <Piece NumberOfPoints="%d" NumberOfCells="%d">\n', ...
    node_num, element_num );
  fprintf ( output_unit, '      <PointData Scalars="scalars">\n' );
  fprintf ( output_unit, '        <DataArray type="Float64" Name="' + data_name + '" Format="ascii">\n' );
  for node = 1 : node_num
    fprintf ( output_unit, '%e ', p(node ) );
    p(node)
  end
  fprintf ( output_unit, '        \n</DataArray>\n' );
  fprintf ( output_unit, '      </PointData>\n' );
  fprintf ( output_unit, '      <Points>\n' );
  fprintf ( output_unit, '        <DataArray type="Float64" NumberOfComponents="3" Format="ascii">\n' );
  for node = 1 : node_num
    fprintf ( output_unit, '%f  %f  %f ', xyz(1:3,node) );
  end
  fprintf ( output_unit, '        \n</DataArray>\n' );
  fprintf ( output_unit, '      </Points>\n' );
  fprintf ( output_unit, '      <Cells>\n' );

  fprintf ( output_unit, '        <DataArray type="Int32" Name="connectivity" Format="ascii">\n' );
  for element = 1 : element_num
    for order = 1 : element_order
      fprintf ( output_unit, '%d ', element_node(order,element) );
    end
    fprintf ( output_unit, '\n' );
  end
  fprintf ( output_unit, '        \n</DataArray>\n' );

  fprintf ( output_unit, '        <DataArray type="Int32" Name="offsets" Format="ascii">\n' );
  offset = 0;
  for element = 1 : element_num
    offset = offset + element_order;
    fprintf ( output_unit, '%d ', offset );
  end
  fprintf ( output_unit, '        \n</DataArray>\n' );
  fprintf ( output_unit, '        <DataArray type="Int32" Name="types" Format="ascii">\n' );
  if ( element_order == 4 )
    for element = 1 : element_num
      fprintf ( output_unit, '10 ' );
    end
  elseif ( element_order == 10 )
    for element = 1 : element_num
      fprintf ( output_unit, '24 ' );
    end
  end
  fprintf ( output_unit, '        \n</DataArray>\n' );

  fprintf ( output_unit, '      </Cells>\n' );
  fprintf ( output_unit, '    </Piece>\n' );
  fprintf ( output_unit, '  </UnstructuredGrid>\n' );
  fprintf ( output_unit, '</VTKFile>\n' );

  return
end
