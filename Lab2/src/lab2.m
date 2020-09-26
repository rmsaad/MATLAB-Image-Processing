%  ELE 882 Lab 2 Report
%  *Authors:*  Rami Saad   (500637869) Section 4
%              Raymond Lam (500759211) Section 2
%% Filtering Functions
%%  Problem 1
    
    % compiling C MEX (function) file
    mex spatial_filter.c
   
    % create h test array
     h = [1   2  1;
          0   0  0;
          -1 -2 -1];
    
    % loading image into matlab Workspace
    F1_OG = imread('peppers.png');
    F1_grey = rgb2gray(F1_OG);
    F1_double = im2double(F1_grey);
    
    % running the function and storing result in out_F1   
    out_F1 = spatial_filter(F1_double, h);
    
    % display results (uncomment to show input)
    imshow(F1_double); title('Grey, Double Type Input');
    imshow(out_F1); title('Filtered Image');

    
%%  Problem 2
    
    % compiling C MEX (function) file
    mex non_max_suppress.c
    
    % running the function and storing result in out_img_Q1   
    out_F2 = non_max_suppress(F1_double, 5, 5);
    
    % display results
    imshow(out_F2); title('Filtered Image');
    
%%  Problem 3
    
    % compiling C MEX (function) file
    mex image_threshold.c
    
    % loading image into matlab Workspace
    T = 0.65;
    
    % running the function and storing result in out_img_Q1   
    out_F3 = image_threshold(F1_double, T);
    
    % display results
    imshow(out_F3); title('Filtered Image');
    
%%  Problem 4
    
    % compiling C MEX (function) file
    mex non_max_suppress.c
    
    % loading image into matlab Workspace
    F4_OG1 = imread('nms-test.png');
    F4_double1 = im2double(F4_OG1);
    
    
    % running the function and storing result in out_img_Q1   
    out_F4 = non_max_suppress(F4_double1, 5, 5);
    
    % display results (uncomment to show orginal)
    imshow(out_F4); title('Filtered Image');
%%  Problem 4 cont
    
    % compiling C MEX (function) file
    mex spatial_filter.c
    
    h = [1 4 7 4 1;
         4 20 33 20 4;
         7 33 55 33 7;
         4 20 33 20 4;
         1 4 7 4 1];
     h = 1/331 * h;
    
    % loading image into matlab Workspace
    F1_OG = imread('peppers.png');
    F1_grey = rgb2gray(F1_OG);
    F1_double = im2double(F1_grey);
    
    
    % running the function and storing result in out_img_Q1   
    out_F4_cont = spatial_filter(F1_double, h);
    
    % display results (uncomment to show orginal)
    imshow(out_F4_cont); title('Filtered Image');
    
%%  Problem 4 cont 2

    % compiling C MEX (function) file
    mex image_threshold.c
    
    % loading image into matlab Workspace
    T = 0.75;
    
    % loading image into matlab Workspace
    F4_OG2 = imread('threshold-test.png');
    F4_double2 = im2double(F4_OG2);
    
    % running the function and storing result in out_img_Q1   
    out_F4_cont2 = image_threshold(F4_double2, T);
    
    % display results
    imshow(out_F4_cont2); title('Filtered Image');
    

%% Edge Detector
%%  Problem 1
    
    
    % loading image into matlab Workspace
    test1 = imread('cameraman.tif');
    edge_detector(test1, derivative_kernel(4), 0.8, 5);
    
%% Derivative Filters
%%  Problem 1
    
    help derivative_kernel;
