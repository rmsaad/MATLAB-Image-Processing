/**
 * @file
 * @brief Simple mex function that applies a linear piecewise function depending on 2 input vectors
 * @author Rami Saad
 * @date September 15, 2019
 *
 * Usage:
 *  >> img_out = contrast_piecewise(img_in, a, b);
 *
 */
#include "mex.h"

/**
 * @brief Implements linear piecewise transform on image of type "uint8".
 * @param[in] width
 *      the width of the image in pixels
 * @param[in] height
 *      the height of the image in pixels
 * @param[in] input
 *      pointer to the first element of the image that we're modifying
 * @param[out] output
 *      pointer to the first element of where the output image will be 
 *      stored
 * @param[in] a_vec[]
 *      a vector utilized in piecewise function
 * @param[in] b_vec[]
 *      b vector utilized in piecewise function
 */
void c_piecewise(int width, int height, const unsigned char *input, unsigned char *output, double a_vec[], double b_vec[]){
     
    // slope of each piecewise segment
    double rise_run_1 = a_vec[1] / a_vec[0];
    double rise_run_2 = (b_vec[1] - a_vec[1]) /(b_vec[0] - a_vec[0]);
    double rise_run_3 = (255 - b_vec[1]) /(255 - b_vec[0]);
    
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
        {
            int ind = x*height + y;
            double temp = 0; 
            
            // application of the piecewise function
            if (input[ind] <= a_vec[0]){
                temp = (double)input[ind]* rise_run_1;
            }else if(input[ind] > a_vec[0] && input[ind] < b_vec[0]){
            	temp = (a_vec[1] - (rise_run_2*a_vec[0])) + ((double)input[ind]*rise_run_2);
            }else if(input[ind] >= b_vec[0]){
            	temp = (b_vec[1] -(rise_run_3*b_vec[0])) + ((double)input[ind]*rise_run_3);
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
        mexErrMsgTxt("contrast_piecewise requires one output argument");
    
    if (nrhs != 3)
        mexErrMsgTxt("contrast_piecewise can only accept three input argument");
    
    const mxArray *img = prhs[0];
    
    // make sure that the input arguments are the right type.
    if (!mxIsUint8(img))
        mexErrMsgTxt("contrast_piecewise can only accept images of type 'uint8'");
    
    // extract the dimensions from the array.
    mwSize ndims = mxGetNumberOfDimensions(img);
    const mwSize *dims = mxGetDimensions(img);
    
    int height   = dims[0];
    int width    = dims[1];
    
    // allocate storage for the output.
    mxClassID input_type = mxGetClassID(img);
    
    mxArray *output = mxCreateNumericArray(ndims, dims, input_type, mxREAL);
    plhs[0] = output;
    
    // variables for a_vec and b_vec
    double *a_vec[2], *b_vec[2];
    a_vec[0] = mxGetPr(prhs[1]); 
    b_vec[0] = mxGetPr(prhs[2]);
    
    // apply processing
    if (mxIsUint8(img))
    {
        unsigned char *img_ptr = (unsigned char *)mxGetData(img);
        unsigned char *out_ptr = (unsigned char *)mxGetData(output);
        
        c_piecewise(width, height, img_ptr, out_ptr, *a_vec, *b_vec);
    }   
}