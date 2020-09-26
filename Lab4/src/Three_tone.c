/**
 * @file
 * @brief Simple mex function that computes a spatial filter
 * @author Rami Saad
 * @date October 14, 2019
 *
 * Usage:
 *  >> img_out = spatial_filter(img_in, h);
 *
 */
#include "mex.h"
#include <math.h>
    
/**
 * @brief Applies spatial on image of type "double".
 * @param[in] width
 *      the width of the image in pixels
 * @param[in] height
 *      the height of the image in pixels
 * @param[in] input
 *      pointer to the first element of the image that we're modifying
 * @param[out] output
 *      pointer to the first element of where the output image will be 
 *      stored
 * @param[in] T
 *      cutoff Threshold
 */
void im_threshold(int width, int height, const double *input, double *output, double TF, double TM, double phi, double HM){
   for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
        {
           int ind = x*height + y;
           
           if(input[ind] >= TF){
                output[ind] = 1;
           }
           else if(input[ind] >= TM && input[ind] < TF){
               output[ind] = 1 + (tanh(phi * (input[ind] - TF)))*(1-HM); 
           }
           else{
               
               output[ind] = (1 + tanh(phi * (input[ind] - TM)))*(HM);
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
        mexErrMsgTxt("image_threshold requires one output argument");
    
    if (nrhs != 5)
        mexErrMsgTxt("image_threshold can only accept three input argument");
    
    const mxArray *img = prhs[0];
    
    // make sure that the input arguments are the right type.
    if (!mxIsDouble(img))
        mexErrMsgTxt("image_threshold can only accept images of type 'uint8'");
    
    // extract the dimensions from the array.
    mwSize ndims = mxGetNumberOfDimensions(img);
    const mwSize *dims = mxGetDimensions(img);
    
    int height   = dims[0];
    int width    = dims[1];
    
    // allocate storage for the output.
    mxClassID input_type = mxGetClassID(img);
    
    mxArray *output = mxCreateNumericArray(ndims, dims, input_type, mxREAL);
    plhs[0] = output;
    
    // variables for rmin and rmax
    double *TF;
    TF = mxGetPr(prhs[1]);
    
    double *TM;
    TM = mxGetPr(prhs[2]);
    
    double *phi;
    phi = mxGetPr(prhs[3]);
    
    double *HM;
    HM = mxGetPr(prhs[4]);
   
    // apply processing
    if (mxIsDouble(img))
    {
        double *img_ptr = (double *)mxGetData(img);
        double *out_ptr = (double *)mxGetData(output);
        
        im_threshold(width, height, img_ptr, out_ptr, *TF, *TM, *phi, *HM);
    }   
}