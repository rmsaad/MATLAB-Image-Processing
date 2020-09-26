%  ELE 882 Lab 1 Report
%  *Authors:*  Rami Saad (500637869)
%% Point Operations
%%  Problem 1
    
    % compiling C MEX (function) file
    mex apply_point_tfrm.c
    
    % loading image into matlab Workspace
    in_img_Q1a = imread('Section2.1 - Q1\183087.jpg');
    in_img_Q1b = imread('Section2.1 - Q1\207056.jpg');
    
    % C and B variables
    C = 1.25;
    B = 10;
    
    % running the function and storing result in out_img_Q1
    out_img_Q1 = apply_point_tfrm(in_img_Q1a,C,B);
    
    % display results (uncomment to show orginal)
    imshow(in_img_Q1a); title('Original');
    imshow(out_img_Q1); title('Point Transformed');
    
%%  Problem 2
    
    % compiling C MEX (function) file
    mex apply_mask.c
    
    % loading image into matlab Workspace
    in_img_Q2a = imread('Section2.1 - Q2\fish.png');
    in_img_Q2b = imread('Section2.1 - Q2\bridge.png');
    in_img_Q2c = imread('Section2.1 - Q2\mask.png');
    
    % running the function and storing result in out_img_Q2
    out_img_Q2 = apply_mask(in_img_Q2a, in_img_Q2b, in_img_Q2c);
    
    % display results (uncomment to show orginals)
    imshow(in_img_Q2a); title('Original');
    imshow(out_img_Q2); title('Mask Image');
    
%%  Problem 3
    
    % compiling C MEX (function) file
    mex average_images.c
    
    % loading image into matlab Workspace
    in_img_Q3a = imread('Section2.1 - Q3\snowglobe_001.png');
    in_img_Q3b = imread('Section2.1 - Q3\snowglobe_002.png');
    in_img_Q3c = imread('Section2.1 - Q3\snowglobe_003.png');
    in_img_Q3d = imread('Section2.1 - Q3\snowglobe_004.png');
    
    % running the function and storing result in out_img_Q3
    out_img_Q3 = average_images(in_img_Q3a, in_img_Q3b, in_img_Q3c, in_img_Q3d);
    
    % display results
    imshow(out_img_Q3); title('Average of Images');
    
%% Contrast Stretching
%%  Problem 1
	
    % compiling C MEX (function) file
    mex contrast_stretch.c
    
    % loading image into matlab Workspace
    in_img_Q_1a = imread('Section2.2 - Q1\183087.jpg');
    in_img_Q_1b = imread('Section2.2 - Q1\motion01.512.tiff');
    
    % rmin and rmax variables
    rmin = 100;
    rmax = 220;
    
    % running the function and storing result in out_img_Q_1
    out_img_Q_1 = contrast_stretch(in_img_Q_1a, rmin, rmax);
    
    % display results
    imshow(out_img_Q_1); title('Contrast Stretched Image');
    
%%  Problem 2
    
    % compiling C MEX (function) file
    mex contrast_piecewise.c
    
    % loading image into matlab Workspace
    in_img_Q_2a = imread('Section2.2 - Q2\7.1.01.tiff');
    in_img_Q_2b = imread('Section2.2 - Q2\7.2.01.tiff');
    
    % variables for a vector and b vector
    a_vec = [60 100]; 
    b_vec = [177 222]; 
    
    % running the function and storing result in out_img_Q_2
    out_img_Q_2 = contrast_piecewise(in_img_Q_2a, a_vec, b_vec);
    
    % display results
    imshow(out_img_Q_2); title('Contrast Piecewise Image');
    
%%  Problem 3
    
    % compiling C MEX (function) file
    mex contrast_highlight.c
    
    % loading image into matlab Workspace
    in_img_Q_3a = imread('Section2.2 - Q3\3096.jpg');
    in_img_Q_3b = imread('Section2.2 - Q3\208001.jpg');
    
    % A, B and I_min variables
    A_3 = 75;
    B_3 = 200;
    I_min = 0;
    
    % running the function and storing result in out_img_Q_3
    out_img_Q_3 = contrast_highlight(in_img_Q_3a, A_3, B_3, I_min);
    
    % display results
    imshow(out_img_Q_3); title('Contrast highlight Image');
    
%%  Problem 4
    
    % compiling C MEX (function) file
    mex contrast_tfrm_curve.c
    
%%  Problem 5
    
    % compiling C MEX (function) file
    mex contrast_tfrm_curve.c
    
    % loading image into matlab Workspace
    in_img_Q_1a = imread('Section2.2 - Q1\183087.jpg');
    in_img_Q_1b = imread('Section2.2 - Q1\motion01.512.tiff');
    
    % rmin and rmax variables
    rmin_5 = 100;
    rmax_5 = 220;
    
    % create LUT for contrast stretching question
    T5 = zeros(1,256); 
    for i = 1:256
        T5(i) = 255*(((1/(rmax_5 - rmin_5))*(i)) - (rmin_5 /(rmax_5 - rmin_5)));
        if T5(i) < 0
            T5(i) = 0;
        elseif T5(i) > 255
            T5(i) = 255;
        end
    end
    
    % running the function and storing result in out_img_Q_5
    out_img_Q_5 = contrast_tfrm_curve(in_img_Q_1a, T5);
    
    %LUT table plot, UNCOMMENT TO VIEW
    %plot(T5); xlabel('Input Intensities, r'); ylabel('Output Intensities, s'); 
    %axis ([0 255 0 255]);
    %set(gca, 'xtick', 0:255/4:255, 'ytick', 0:255/4:255);
    %set(gca, 'yticklabel', {'0', 'L/4', 'L/2', '3L/4', 'L-1'});
    %set(gca, 'xticklabel', {'0', 'L/4', 'L/2', '3L/4', 'L-1'});
    
    % display results
    imshow(out_img_Q_5); title('Contrast Stretching LUT Image');
    
    
%%  Problem 6
    %%  Question 2 LUT
    
    % compiling C MEX (function) file
    mex contrast_tfrm_curve.c
    
    % loading image into matlab Workspace
    in_img_Q_2a = imread('Section2.2 - Q2\7.1.01.tiff');
    in_img_Q_2b = imread('Section2.2 - Q2\7.2.01.tiff');
    
    % a vector and b vector variables
    a_vec_6 = [60 100]; 
    b_vec_6 = [177 222]; 
    
    % slope of each piecewise segment
    rise_run_1 = a_vec_6(2) / a_vec_6(1);
    rise_run_2 = (b_vec_6(2) - a_vec_6(2)) /(b_vec_6(1) - a_vec_6(1));
    rise_run_3 = (255 - b_vec_6(2)) /(255 - b_vec_6(1));
    
    % create LUT for piecewise question
    T6a = zeros(1,256);
    for i = 1:256
        if i <= a_vec_6(1)
            T6a(i) = (i * rise_run_1); 
        elseif i > a_vec_6(1) && i < b_vec_6(1)
            T6a(i) = (i * rise_run_2) + (a_vec_6(2) -(rise_run_2 * a_vec_6(1)));
        elseif i >= b_vec_6(1)
            T6a(i) = (i * rise_run_3) + (b_vec_6(2) -(rise_run_3 * b_vec_6(1))); 
        end    
    end
    
    % running the function and storing result in out_img_Q_6a
    out_img_Q_6a = contrast_tfrm_curve(in_img_Q_2a, T6a);
    
    %LUT table plot, UNCOMMENT TO VIEW
    %plot(T6a); xlabel('Input Intensities, r'); ylabel('Output Intensities, s'); 
    %axis ([0 255 0 255]);
    %set(gca, 'xtick', 0:255/4:255, 'ytick', 0:255/4:255);
    %set(gca, 'yticklabel', {'0', 'L/4', 'L/2', '3L/4', 'L-1'});
    %set(gca, 'xticklabel', {'0', 'L/4', 'L/2', '3L/4', 'L-1'});
    
    % display results
    imshow(out_img_Q_6a); title('Piecewise LUT Image');
    
    %%  Question 3 LUT
    
    % compiling C MEX (function) file
    mex contrast_tfrm_curve.c
    
    % loading image into matlab Workspace
    in_img_Q_3a = imread('Section2.2 - Q3\3096.jpg');
    in_img_Q_3b = imread('Section2.2 - Q3\208001.jpg');
    
    % A, B and I_min variables
    A_6b = 50;
    B_6b = 200;
    I_min6b = 0;
    
    % create LUT for contrast highlight question
    T6b = zeros(1,256); 
    for i = 1:256
        if i <= A_6b
            T6b(i) = I_min6b;
        elseif i > A_6b && i < B_6b 
            T6b(i) = i;
        elseif i >= B_6b
            T6b(i) = I_min6b;
        end
    end
    
    % running the function and storing result in out_img_Q_6b
    out_img_Q_6b = contrast_tfrm_curve(in_img_Q_3a, T6b);
    
    %LUT table plot, UNCOMMENT TO VIEW
    %plot(T6b); xlabel('Input Intensities, r'); ylabel('Output Intensities, s'); 
    %axis ([0 255 0 255]);
    %set(gca, 'xtick', 0:255/4:255, 'ytick', 0:255/4:255);
    %set(gca, 'yticklabel', {'0', 'L/4', 'L/2', '3L/4', 'L-1'});
    %set(gca, 'xticklabel', {'0', 'L/4', 'L/2', '3L/4', 'L-1'});
    
    % display results
    imshow(out_img_Q_6b); title('Contrast Highlight LUT Image');
    

