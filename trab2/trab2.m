function rotObj (degrees, matrix)
  figure(1); # Sets a new plot window
  clf; # Clears the window
  axis([-5 5 -5 5], "square"); # Limit the window plot
  
  rad = degrees * (pi/180); # Converts degrees to radians
  
  # Rotation matrix
  rot = [cos(rad) -sin(rad) 0;
         sin(rad)  cos(rad) 0;
         0         0        1];
         
  rot_obj = rot * matrix; # Rotates the object
  
  # Plotting the matrix
  plotObj(matrix)
  plotObj(rot_obj)
endfunction

function plotObj (matrix)
  hold on;
  
  for i = 1:size(matrix,2)
    plot(matrix(1,i), matrix(2,i));
    if (i < size(matrix,2))
      line([matrix(1,i), matrix(1,i+1)],
           [matrix(2,i), matrix(2,i+1)]);
    else
      line([matrix(1,i), matrix(1,1)],
           [matrix(2,i), matrix(2,1)]);
    endif  
  endfor
  
  hold off;
endfunction