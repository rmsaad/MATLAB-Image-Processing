/**
 * @file
 * @brief Simple mex function that computes the average of n images
 * @author Rami Saad
 * @date September 14, 2019
 *
 * Usage:
 *  >> img_out = average_images(img_in_1, img_in_2, img_in_3, img_in_4);
 *
 */
#include <stdio.h>
#include "mex.h"

/**
 * @brief averages images of type "uint8".
 * @param[in] width
 *      the width of the image in pixels
 * @param[in] height
 *      the height of the image in pixels
 * @param[in] input
 *      pointer to the first element of the first image that we're modifying (2D array)
 * @param[out] output
 *      pointer to the first element of where the output image will be 
 *      stored
 * @param[in] n
 *      number of images
 */
void a_mask(int width, int height, unsigned char **input, unsigned char *output, int n){
     
    // reciprical of the number of images
    double d = 1/(double)n;
   
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
        {
           int ind = x*height + y;
         
         double temp = 0;
         
         // averaging pixel intensity of all pixels from every picture
         for(int j = 0; j<n; j++){
            temp = temp + (d * (double)(input[j][ind]));
         }
         
         // ensure that the image intensity is within correct bounds
         if(temp > 255)
               temp = 255;
         if (temp < 0)
               temp = 0;
         
         // assign temp value to correct place in output index 
         output[ind] = (int)temp;
            
        }
}

/**
 * @brief Main entry point into the mex function.
 * @param[in] nlhs
 *      the number of <em>input</em> arguments
 * @param[in] plhs
 *      an array of pointers to the matlab array objects
 * @param[in] nrhs
 *      the number of <em>output</em> arguments
 * @param[out] prhs
 *      an array of uninitialized matlab array objects where the output 
 *      will be stored
 */
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    
    // check that the number of input and output arguments are correct and 
    // otherwise mex function will crash and display an error message
    if (nlhs != 1)
        mexErrMsgTxt("average_images requires one output argument");
    
    if (nrhs < 2)
        mexErrMsgTxt("average_images can only accept two or more input argument");
    
    const mxArray *img[nrhs];
    
    // make sure that the input arguments are the right type.
    for (int n = 0; n < nrhs; n++){
        img[n] = prhs[n];
        if(!mxIsUint8(img[n]))
            mexErrMsgTxt("average_images can only accept images of type 'uint8'");
    }
  
    // extract the dimensions from the array. 
    mwSize ndims = mxGetNumberOfDimensions(img[0]);
    const mwSize *dims = mxGetDimensions(img[0]);
    
    int height   = dims[0];
    int width    = dims[1];
    
    // allocate storage for the output.
    mxClassID input_type = mxGetClassID(img[0]);
    
    mxArray *output = mxCreateNumericArray(ndims, dims, input_type, mxREAL);
    plhs[0] = output;
    
    // create 2D array
    unsigned char *img_ptr[nrhs];
    
    // fill 2D array
    for (int m = 0; m < nrhs; m++){
        if (mxIsUint8(img[m]))
           img_ptr[m] = (unsigned char *)mxGetData(img[m]); 
    }
    
    unsigned char *out_ptr  = (unsigned char *)mxGetData(output);
    
    // apply processing
    a_mask(width, height, img_ptr, out_ptr, nrhs);
     
}