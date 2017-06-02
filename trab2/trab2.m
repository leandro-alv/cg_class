function rotObj (degrees, matrix)
  figure(1); # Sets a new plot window
  clf; # Clears the window
  axis([-5 5 -5 5], "square"); # Limit the window plot
  
  rad = degrees * (pi/180); # Converts degrees to radians
  px = 0 - ((max(matrix(1,:)) - min(matrix(1,:))) / 2.0);
  py = 0 - ((max(matrix(2,:)) - min(matrix(2,:))) / 2.0);
  
  # Rotation matrix
  transl = [1 0 px;
            0 1 py;
            0 0 1];

  rot = [cos(rad) -sin(rad) 0;
         sin(rad)  cos(rad) 0;
         0         0        1];
  
  rot_obj = (inv(transl) * rot * transl) * matrix;
  
  # Plotting the matrix
  plotObj(matrix);
  plotObj(rot_obj);
endfunction

function plotObj (matrix)
  hold on;
  
  i = size(matrix,2);
  line([matrix(1,:)], [matrix(2,:)]);
  line([matrix(1,i), matrix(1,1)],
       [matrix(2,i), matrix(2,1)]);
  
  hold off;
endfunction