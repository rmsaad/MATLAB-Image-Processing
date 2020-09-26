function out = gaussian(choice)

% >> returns a mask based on the input argument choice
% >>
% >> if gaussian(1): 1x1 gaussian
% >> if gaussian(2): 2x2 gaussian
% >> if gaussian(3): 3x3 gaussian
% >> otherwise returns an error message
% >>
% >> sample usage: spatial_filter(image, derivative_kernel(4));


g_1x1  = [1];

g_3x3  = 1/16 * [1 2 1;
                 2 4 2;
                 1 2 1];

g_5x5 = 1/331 * [1  4  7  4 1;
                 4 20 33 20 4;
                 7 33 55 33 7;
                 4 20 33 20 4;
                 1  4  7  4 1];
          
switch choice
    case 1
        out = g_1x1;
    case 3
        out = g_3x3;
    case 5
        out = g_5x5;
    otherwise
        error("Not a suitable input argument");    
end

end