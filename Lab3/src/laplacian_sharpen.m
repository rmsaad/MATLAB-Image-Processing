function out = laplacian_sharpen(img , k)
    mex spaitial_filter.c
    img = im2double(img);
    h = [-1 -1 -1; 
         -1  8 -1;
         -1 -1 -1];
    
    out = img + k.*(spaitial_filter(img,h));
end