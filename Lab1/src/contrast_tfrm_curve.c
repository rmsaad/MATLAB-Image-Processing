/**
 * @file
 * @brief Simple mex function that manipulates image intensity given a input transfer function LUT
 * @author Rami Saad
 * @date September 15, 2019
 *
 * Usage:
 *  >> img_out = contrast_tfrm_curve(img_in, T);
 *
 */
#include "mex.h"

/**
 * @brief Utilizes LUT on image of type "uint8".
 * @param[in] width
 *      the width of the image in pixels
 * @param[in] height
 *      the height of the image in pixels
 * @param[in] input
 *      pointer to the first element of the image that we're modifying
 * @param[out] output
 *      pointer to the first element of where the output image will be 
 *      stored
 * @param[in] T[]
 *      Transfer function LUT
 */
void c_tfrm_curve(int width, int height, const unsigned char *input, unsigned char *output, double T[]){
    
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
        {
            int ind = x*height + y;
            double temp = 0; 
            
            // applies LUT
            temp = T[input[ind]];
            
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
        mexErrMsgTxt("contrast_tfrm_curve requires one output argument");
    
    if (nrhs != 2)
        mexErrMsgTxt("contrast_tfrm_curve can only accept three input argument");
    
    const mxArray *img = prhs[0];
    
    // make sure that the input arguments are the right type.
    if (!mxIsUint8(img))
        mexErrMsgTxt("contrast_tfrm_curve can only accept images of type 'uint8'");
    
    // extract the dimensions from the array.  
    mwSize ndims = mxGetNumberOfDimensions(img);
    const mwSize *dims = mxGetDimensions(img);
    
    int height   = dims[0];
    int width    = dims[1];
    
    // allocate storage for the output.
    mxClassID input_type = mxGetClassID(img);
    
    mxArray *output = mxCreateNumericArray(ndims, dims, input_type, mxREAL);
    plhs[0] = output;
    
    // variables for LUT
    double *T[256];
    T[0] = mxGetPr(prhs[1]); 
    
    // apply processing
    if (mxIsUint8(img))
    {
        unsigned char *img_ptr = (unsigned char *)mxGetData(img);
        unsigned char *out_ptr = (unsigned char *)mxGetData(output);
        
        c_tfrm_curve(width, height, img_ptr, out_ptr, *T);
    }   
}