function edges = edge_detector ( img , H , T , wndsz )
% Detect edges in an image .
%
% Inputs :
% img
% image being processed ( can be either greyscale or RGB )
% H
% the filtering kernel that approximates the horizontal
% derivative
% T [ optional ]
% the threshold value used by the edge detector ( default is
% 0.1)
% wndsz [ optional ]
% the size of the NMS filter window ( default is 5)
%
% Outputs :
% edges
% a binary image where a value of ’1 ’ indicates an image edge
img = im2double ( img );
% if ‘img ’ is a colour image , convert it to greyscale first
if size ( img ,3) > 1
img = rgb2gray ( img );
end
% ‘ nargin ’ returns the number of input arguments so you can set
% arguments that have not been provided
if nargin == 2
T = 0.1;
wndsz = 5;
end
% TODO - Fill in with your processing code
    % compiling C MEX (function) file

    mex spatial_filter.c
    mex non_max_suppress.c
    mex image_threshold.c
    
    % running the function and storing result in out_img_Q1   
    out_x = spatial_filter(img, H);
    out_y = spatial_filter(img, transpose(H));

    G = sqrt((out_x.*out_x)+(out_y.*out_y)) / 2;
    
    G2 = non_max_suppress(G, wndsz, wndsz);
    
    G3 = image_threshold(G2, T);
    
    % display results (uncomment to show orginal)
    imshow(G3); title('Filtered Image')
