%  ELE 882 Lab 4 Report
%  *Authors:*  Rami Saad   (500637869) Section 4
%              Raymond Lam (500759211) Section 2
%% Enhancement XDog
%%  Problem 1
    
    % compiling C MEX (function) file
    mex gaussian_kern.c
    mex spaitial_filter.c
    
    % loading image into matlab Workspace
    img_in_1  = rgb2gray(im2double(imread('peppers.png')));
    
    % create 2 gaussian kernels and specify p
    gaus1 = gaussian_kern(0.9, 5);
    gaus2 = gaussian_kern(1.2*0.9, 5);
    p = 100;
    
    % running the function and storing result in img_out_2111   
    img_out_1 = spaitial_filter(img_in_1, gaus1); 
    img_out_2 = spaitial_filter(img_in_1, gaus2);
    im_final = ((1+p)*img_out_1 - (p)*img_out_2); 
    
    % display results (uncomment to show input)
    %imshow(img_in_1);
    imshow(im_final);
    
%%  Problem 2 hard threshold
    
    % compiling C MEX (function) file
    mex hard_threshold.c
    
    % running the function and storing result in img_out_2112   
    im_hard = hard_threshold(im_final, 0.85);
    
    % display results (uncomment to show input)
    imshow(im_hard);
    
%%  Problem 2 Soft threshold
    
    % compiling C MEX (function) file
    mex soft_threshold.c
    
    % running the function and storing result in img_out_2112   
    im_soft = soft_threshold(im_final, 0.85, 3);
    
    % display results (uncomment to show input)
    imshow(im_soft);
    
%%  Problem 2 Plot

    T = 0.85;
    phi = 3;
    
    x1 = (0:0.01:T);
    y1 = 1 + tanh(phi * (x1 - T));

    x2 = (T:0.01:1);
    y2 = ones(1, length(x2));

    x = [x1 x2];
    y = [y1 y2];

    plot(x, y);
    
    xlabel('Input Intensities, r'); ylabel('Output Intensities, s'); 
    axis ([0 1 0 1]);
    set(gca, 'xtick', 0:1/4:1, 'ytick', 0:1/4:1);
    set(gca, 'yticklabel', {'0', 'L/4', 'L/2', '3L/4', 'L-1'});
    set(gca, 'xticklabel', {'0', 'L/4', 'L/2', '3L/4', 'L-1'});
    
%%  Problem 3
    
    % compiling C MEX (function) file
    mex Three_tone.c
    
    % running the function and storing result in img_out_2113   
     im_three = Three_tone(im_final, 0.85, 0.4, 15, 0.4);
     
    % display results (uncomment to show input)
    imshow(im_three);
    
%%  Problem 3 Plot

    TF = 0.85; % second threshold
    TM = 0.4; %  first threhold
    HM = 0.4; %  height middle tone
    phi = 15;

    x1 = (0:0.01:TM);
    y1 = (1 + tanh(phi * (x1 - TM)))*(HM);
    x2 = (TM:0.01:TF);
    y2 = 1 + (tanh(phi * (x2 - TF)))*(1-HM);

    x3 = (TF:0.01:1);
    y3 = ones(1, length(x3));

    x = [x1 x2 x3];
    y = [y1 y2 y3];
    plot(x, y);

    xlabel('Input Intensities, r'); ylabel('Output Intensities, s'); 
    axis ([0 1 0 1]);
    set(gca, 'xtick', 0:1/4:1, 'ytick', 0:1/4:1);
    set(gca, 'yticklabel', {'0', 'L/4', 'L/2', '3L/4', 'L-1'});
    set(gca, 'xticklabel', {'0', 'L/4', 'L/2', '3L/4', 'L-1'});

%% Cartoon Effect
%%  Problem 1
    
    % compiling C MEX (function) file
    mex median.c
    
    % loading image into matlab Workspace
    img_in_1  = rgb2gray(im2double(imread('pears.png')));
    
    % running the function and storing result in img_out_2111   
    im_temp1 = median(img_in_1, 1, 21);
    im_fin = median(im_temp1, 5, 1);
    
    % display results (uncomment to show input)
    imshow(im_fin);
   
%%  Problem 2

    % compiling C MEX (function) file
    mex gaussian_kern.c
    mex spaitial_filter.c
    
    % loading image into matlab Workspace
    img_in_1  = rgb2gray(im2double(imread('pears.png')));
    
    % create 2 gaussian kernels and specify p
    gaus1 = gaussian_kern(0.9, 5);
    gaus2 = gaussian_kern(1.2*0.9, 5);
    p = 100;
    
    % running the function and storing result in img_out_2111   
    img_out_1 = spaitial_filter(img_in_1, gaus1); 
    img_out_2 = spaitial_filter(img_in_1, gaus2);
    im = img_out_1 - img_out_2;
    
    G3 = hard_threshold(im, 0.001);
    G4 = median(G3, 5, 5);
    
    G5 = spaitial_filter(G4, gaus2);
    G5 = hard_threshold(im, 0.00001);
    
    imshow(G5);

%%  Problem 3
    
    % compiling C MEX (function) file
    mex combine.c
    
    % running the function and storing result in img_out_2113   
    ii = combine(G5, im_fin);
    
    % display results (uncomment to show input)
   imshow(ii);