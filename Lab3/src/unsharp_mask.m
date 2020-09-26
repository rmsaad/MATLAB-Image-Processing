function [ out ] = unsharp_mask( img, r, k )
mex spaitial_filter.c
img = im2double(img);
out = img + (k*(imsubtract(img,spaitial_filter(img, gaussian(r)))));
end