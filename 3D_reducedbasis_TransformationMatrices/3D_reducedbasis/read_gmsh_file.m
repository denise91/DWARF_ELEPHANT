function [ node_x, element_node ] = read_gmsh_file ( gmsh_filename, node_dim, element_order )

%*****************************************************************************
%
%% GMSH_DATA_READ reads data from a GMSH file.
%
%  Licensing:
%
%    This code is distributed under the GNU LGPL license.
%
%  Modified:
%
%    23 October 2014
%
%  Author:
%
%    John Burkardt
%
%  Parameters:
%
%    Input, string GMSH_FILENAME, the GMSH filename.
%
%    Input, integer NODE_DIM, the spatial dimension.
%
%    Input, integer NODE_NUM, the number of nodes.
%
%    Input, integer ELEMENT_ORDER, the order of the elements.
%
%    Output, real NODE_X(NODE_DIM,NODE_NUM), the node coordinates.
%
%    Output, integer ELEMENT_NODE(ELEMENT_ORDER,ELEMENT_NUM), 
%    the nodes that make up each element.
%
  node_x = zeros ( node_dim, 3000000 );
  element_node = zeros ( element_order, 5000000 );
%
%  Open the file.
%
  input = fopen ( gmsh_filename, 'rt' );

  if ( input < 0 )
    fprintf ( 1, '\n' );
    fprintf ( 1, 'GMSH_DATA_READ - Error!\n' );
    fprintf ( 1, '  Could not open the input file "%s".\n', gmsh_filename );
    error ( 'GMSH_DATA_READ - Error!' );
    return
  end

  level = 0;

  while ( true )

    text = fgetl ( input );

    if ( text == -1 )
      break
    end

    if ( level == 0 )
      if ( s_begin ( text(1:end), '$Nodes' ) )
        level = 1;
        j = 0;
      end
    elseif ( level == 1 )
      [ value, count ] = sscanf ( text, '%d' );
      level = 2;
    elseif ( level == 2 )
      if ( s_begin ( text(1:end), '$EndNodes' ) )
        break
      else
        j = j + 1;
        [ value, count ] = sscanf ( text, '%d  %f  %f  %f' );
        indx = value(1);
        node_x(1,j) = value(2);
        if ( 2 < count )
          node_x(2,j) = value(3);
          if ( 3 < count )
            node_x(3,j) = value(4);
          end
        end
      end
    end

  end
  node_x(:,j+1:end) = [];
%
%  Now read element information.
%
  level = 0;

  while ( true )

    text = fgetl ( input );

    if ( text == -1 )
      fprintf ( 'ran out\n' );
      break
    end

    if ( level == 0 )
      if ( s_begin ( text(1:9), '$Elements' ) )
        level = 1;
        j = 0;
      end
    elseif ( level == 1 )
      [ value, count ] = sscanf ( text, '%d' );
      level = 2;
    elseif ( level == 2 )
      if ( s_begin ( text(1:12), '$EndElements' ) )
        break
      else
        [ value, count ] = sscanf ( text, '%d' );
		if (count == 9)
		  j = j + 1;
          for i = 1 : element_order
            element_node(i,j) = value(5+i);
          end
		end
      end
    end

  end
  element_node(:,j+1:end) = [];
  fclose ( input );

  return
end
