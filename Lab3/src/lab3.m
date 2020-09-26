%  ELE 882 Lab 3 Report
%  *Authors:*  Rami Saad   (500637869) Section 4
%              Raymond Lam (500759211) Section 2
%% Enhancement Operators & Testing
%%  Problem 1
    
    % compiling C MEX (function) file
    mex histogram_equalize.c
    
    % loading image into matlab Workspace
    img_in_2111_1  = imread('Images\testing\contrast\7.2.01-small.png');
    img_in_2111_2  = imread('Images\testing\contrast\207056.jpg');
    
    % running the function and storing result in img_out_2111   
    img_out_2111 = histogram_equalize(img_in_2111_1);
    img_out_2112 = histogram_equalize(img_in_2111_2);
    
    % display results (uncomment to show input)
    subplot(1,2,2)
    imshow(img_out_2111); title('Histogram Equalized');
    subplot(1,2,1)
    imshow(img_out_2112); title('Histogram Equalized');
    
%%  Problem 2
    
    % compiling C MEX (function) file
    mex adaptive_histogram.c
    
    % loading image into matlab Workspace
    img_in_2112_1  = imread('Images\testing\contrast\7.2.01-small.png');
    img_in_2112_2  = imread('Images\testing\contrast\207056.jpg');
    
    % running the function and storing result in img_out_2112   
    img_out_2112_1 = adaptive_histogram(img_in_2112_1, 75, 75);
    img_out_2112_2 = adaptive_histogram(img_in_2112_2, 55, 55);
    
    % display results (uncomment to show input)
    subplot(1,2,2)
    imshow(img_out_2112_1); title('Local Histogram Equalize');
    subplot(1,2,1)
    imshow(img_out_2112_2); title('Local Histogram Equalize');
    
%%  Problem 3
    
    % loading image into matlab Workspace
    img_in_2113_1  = imread('Images\testing\sharpen\7.2.01-small.png');
    img_in_2113_2  = imread('Images\testing\sharpen\digital_orca_blurred.png');
    
    % running the function and storing result in img_out_2113   
    img_out_2113_1 = unsharp_mask(img_in_2113_1, 5, 5);
    img_out_2113_2 = unsharp_mask(img_in_2113_2, 5, 5);
    
    % display results (uncomment to show input)
    subplot(1,2,2)
    imshow(img_out_2113_1);
    subplot(1,2,1)
    imshow(img_out_2113_2);
    
%%  Problem 4
    
    % loading image into matlab Workspace
    img_in_2114_1  = imread('Images\testing\sharpen\7.2.01-small.png');
    img_in_2114_2  = imread('Images\testing\sharpen\digital_orca_blurred.png');
    
    % running the function and storing result in img_out_2114   
    img_out_2114_1 = laplacian_sharpen(img_in_2114_1, 1.5);
    img_out_2114_2 = laplacian_sharpen(img_in_2114_2, 2);
    
    % display results (uncomment to show input)
    subplot(1,2,2)
    imshow(img_out_2114_1);
    subplot(1,2,1)
    imshow(img_out_2114_2);
    
%% Enhancement
%%  Problem 1
    %% noise additive.png
    
    % loading image into matlab Workspace
    img_in_221  = imread('Images\enhance\noise_additive.png');
    
    % running the function and storing result in img_out_221
    img_out_221 = spaitial_filter(im2double(img_in_221), gaussian(3));
    
    % display results (uncomment to show input)
    subplot(1,2,2);
    imshow(img_out_221); title('Output');
    subplot(1,2,1)
    imshow(img_in_221); title('Input');
    
     %% noise multiplicative.png
    
    % loading image into matlab Workspace
    img_in_222  = imread('Images\enhance\noise_multiplicative.png');
    
    % running the function and storing result in img_out_222
    img_out_222 = spaitial_filter(im2double(img_in_222), gaussian(5));
    img_out_222 = unsharp_mask(img_out_222, 3, 1.5);
    img_out_222 = laplacian_sharpen(img_out_222, 0.35);
    
    % display results (uncomment to show input)
    subplot(1,2,2);
    imshow(img_out_222); title('Output');
    subplot(1,2,1)
    imshow(img_in_222); title('Input');
    
     %% noise impulsive.png
    
    % loading image into matlab Workspace
    img_in_223  = imread('Images\enhance\noise_impulsive.png');
    
    % running the function and storing result in img_out_223
    img_out_223 = medfilt2(img_in_223);
    
    % display results (uncomment to show input)
    subplot(1,2,2);
    imshow(img_out_223); title('Output');
    subplot(1,2,1)
    imshow(img_in_223); title('Input');
     %% snowglobe.png
    
    % loading image into matlab Workspace
    img_in_224  = imread('Images\enhance\snowglobe.png');
    
    % running the function and storing result in img_out_224
    img_out_224 = medfilt2(img_in_224);
    img_out_222 = laplacian_sharpen(img_out_224, 2);
    
    % display results (uncomment to show input)
    subplot(1,2,2);
    imshow(img_out_224); title('Output');
    subplot(1,2,1)
    imshow(img_in_224); title('Input');
    
%% Analysis
%%  Problem 1
    % A guassian filter was used to handle the additive noise as it is the
    % spaitial representation of a low pass filter. Since all noise is high
    % frequency this was ideal. As excessive blurring might have become a 
    % proble we decided on a kernel size of only 3. For the Multiplcative 
    % noise first we ran it through a guassian filter for the same reasons
    % as above, then passed the result through a unsharpening mask and
    % laplacian filter respectively, this was done to increase contrast and
    % make edges more apparently visable after the harsher gassian filter.
    % Finally the median filter was used on the salt and pepper noise as
    % that filter is very good at removing outliers and that is
    % particuallarly what the impulsive noise is composed of (large or 
    % small values). 
    
%%  Problem 2
    % The course textbook goes over methods for dealing with both additive
    % and multiplacative noise. For Additive noise the Wiener filter should
    % have been utilized which produces an output through a linear time
    % invarient fitlering process. For multiplacative noise, Homomorphic 
    % filtering should have been used which entails a nonlinear mapping to
    % different domains. For the sake of brevity and time contraints a
    % comprimise with the guassian filter was utilized. The median filter 
    % was in fact the best method as it remvoved exactly the lowest and
    % highest noise intensity values. 
    
%%  Problem 3
    % Global histogram equalization affects the entire image where the
    % histogram for the entire image will become more uniform which 
    % enhances the contrast of the image. Local histogram equalization will
    % target a window size where it would perform histogram equalization on
    % this window size which is a smaller image. Usually local histogram 
    % equalization results in a subjective “worst” image since if it were
    % perform in a dark area of a image it would make certain slightly
    % dark pixel lighter and other dark pixel  darker to achieve histogram
    % equalization and in a situation the local histogram equalization was
    % performed on a light area, it would make certain light pixels darker
    % and very light pixel lighter. Local histogram equalization does not 
    % consider the entire and it may distort the image. The global 
    % operation considers the entire image where the dark pixels become 
    %darker and the light pixel become lighter. 
    
%%  Problem 4
    %Unsharp masking is when blur the original image and subtract this
    %blurred image from the original image to obtain a unsharp mask to the
    %original filter. The unsharp mask is multiply by some constant k and 
    %then added to the original image to achieve a certain effect; k<1 to 
    %deemphasizes, k = 1 to unsharp mask and K>1 to high boost filtering.

%Laplacian is very sensitive to noise and need to be pre-filtered, usually 
%combined with the gaussian mask to perform noise filtering and edge detection.

%Unsharp masking is better since it  does noise filtering through the 
%blurring stage, it is also more flexible since we can control the amount 
%of blurring and the sharpening strength when adding the unsharp mask to the original image.


    
    
    
    
    
    
    
    
    
    