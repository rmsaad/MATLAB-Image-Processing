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
void a_mask(int width, int height, const double *input0, const double *input1,  double *output){

     for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
        {
           int ind = x*height + y;
           
           // depending on the mask value the image intensity of input0 or input1 will be stored to output 
           if(input0[ind] > 0){
                output[ind] = input1[ind];
           }
           else if(input0[ind] == 0){
                output[ind] = input0[ind];
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
    
    if (nrhs != 2)
        mexErrMsgTxt("apply_mask can only accept three input argument");
    
    const mxArray *img0 = prhs[0];
    const mxArray *img1 = prhs[1];
    
    // make sure that the input arguments are the right type.
    if (!mxIsDouble(img0) || !mxIsDouble(img1))
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
    if (mxIsDouble(img0) && mxIsDouble(img1))
    {
        double *img_ptr0 = (double *)mxGetData(img0);
        double *img_ptr1 = (double *)mxGetData(img1);
        double *out_ptr  = (double *)mxGetData(output);
        
        a_mask(width, height, img_ptr0, img_ptr1, out_ptr);
    }   
}