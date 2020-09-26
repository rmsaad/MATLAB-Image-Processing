/**
 * @file
 * @brief Simple mex function that takes in 3 images and applies a mask
 * @author Rami Saad
 * @date September 14, 2019
 *
 * Usage:
 *  >> img_out = = apply_mask(img_in_1, img_in_2, img_in_3);
 *
 */
#include "mex.h"

/**
 * @brief applies mask on two images of type "uint8" and "logical".
 * @param[in] width
 *      the width of the image in pixels
 * @param[in] height
 *      the height of the image in pixels
 * @param[in] input0
 *      pointer to the first element of the first image that we're modifying
 * @param[in] input1
 *      pointer to the first element of the second image that we're modifying
 * @param[in] input2
 *      pointer to the first element of the third image that we're modifying
 * @param[out] output
 *      pointer to the first element of where the output image will be 
 *      stored
 */
void a_mask(int width, int height, const unsigned char *input0, const unsigned char *input1, const unsigned char *input2, unsigned char *output){

     for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
        {
           int ind = x*height + y;
           
           // depending on the mask value the image intensity of input0 or input1 will be stored to output 
           if(input2[ind] > 0){
                output[ind] = input0[ind];
           }
           else if(input2[ind] == 0){
                output[ind] = input1[ind];
           }
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
        mexErrMsgTxt("apply_mask requires one output argument");
    
    if (nrhs != 3)
        mexErrMsgTxt("apply_mask can only accept three input argument");
    
    const mxArray *img0 = prhs[0];
    const mxArray *img1 = prhs[1];
    const mxArray *img2 = prhs[2];
    
    // make sure that the input arguments are the right type.
    if (!mxIsUint8(img0) || !mxIsUint8(img1) || !mxIsLogical(img2))
        mexErrMsgTxt("apply_mask can only accept images of type 'uint8' and 'logical'");
    
    // extract the dimensions from the array.
    mwSize ndims = mxGetNumberOfDimensions(img0);
    const mwSize *dims = mxGetDimensions(img0);
    
    int height   = dims[0];
    int width    = dims[1];
    
    // allocate storage for the output.
    mxClassID input_type = mxGetClassID(img0);
    
    mxArray *output = mxCreateNumericArray(ndims, dims, input_type, mxREAL);
    plhs[0] = output;
    
    // apply processing
    if (mxIsUint8(img0) && mxIsUint8(img1) && mxIsLogical(img2))
    {
        unsigned char *img_ptr0 = (unsigned char *)mxGetData(img0);
        unsigned char *img_ptr1 = (unsigned char *)mxGetData(img1);
        unsigned char *img_ptr2 = (unsigned char *)mxGetData(img2);
        unsigned char *out_ptr  = (unsigned char *)mxGetData(output);
        
        a_mask(width, height, img_ptr0, img_ptr1, img_ptr2, out_ptr);
    }   
}