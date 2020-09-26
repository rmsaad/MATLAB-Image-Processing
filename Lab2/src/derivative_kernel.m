function out = derivative_kernel(choice)

% >> returns a mask based on the input argument choice
% >>
% >> if derivative_kernel(1): outputs a Central Difference Mask
% >> if derivative_kernel(2): outputs Forward Difference Mask
% >> if derivative_kernel(3): outputs Prewitt Mask
% >> if derivative_kernel(4): outputs Sobel Mask
% >> otherwise returns an error message
% >>
% >> sample usage: spatial_filter(image, derivative_kernel(4));


h_Central  = [1 0 -1];

h_Forward  = [0 1 -1];

h3_Prewitt = [1 0 -1;
              1 0 -1; 
              1 0 -1];
  
h_Sobel    = [1 0 -1;
              2 0 -2;
              1 0 -1];

switch choice
    case 1
        out = h_Central;
    case 2
        out = h_Forward;
    case 3
        out = h3_Prewitt;
    case 4
        out = h_Sobel;
    otherwise
        error("Not a suitable input argument");    
end

end

