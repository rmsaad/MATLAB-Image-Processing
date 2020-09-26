/**
 * @file
 * @brief Simple mex function that filters image given 2 image intensity ranges (0 - A, B - 255)
 * @author Rami Saad
 * @date September 15, 2019
 *
 * Usage:
 *  >> img_out = contrast_highlight(img_in, A, B, I_min);
 *
 */
#include "mex.h"

/**
 * @brief Highlights contrast of image of type "uint8".
 * @param[in] width
 *      the width of the image in pixels
 * @param[in] height
 *      the height of the image in pixels
 * @param[in] input
 *      pointer to the first element of the image that we're modifying
 * @param[out] output
 *      pointer to the first element of where the output image will be 
 *      stored
 * @param[in] A
 *      first  value of [r] range
 * @param[in] B
 *      second value of [r] range
 * @param[in] I_min
 *      image intensity value to set the two range to
 */
void c_piecewise(int width, int height, const unsigned char *input, unsigned char *output, double A, double B, double I_min){
     
    
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
        {
            int ind = x*height + y;
            double temp = 0; 
            
            // implementing contrast highlight function
            if (input[ind] <= A){
                temp = I_min;
            }else if(input[ind] > A && input[ind] < B){
            	temp = input[ind];
            }else if(input[ind] >= B){
            	temp = I_min;
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
        mexErrMsgTxt("contrast_highlight requires one output argument");
    
    if (nrhs != 4)
        mexErrMsgTxt("contrast_highlight can only accept three input argument");
    
    const mxArray *img = prhs[0];
    
    // make sure that the input arguments are the right type.
    if (!mxIsUint8(img))
        mexErrMsgTxt("contrast_highlight can only accept images of type 'uint8'");
    
    // allocate storage for the output.
    mwSize ndims = mxGetNumberOfDimensions(img);
    const mwSize *dims = mxGetDimensions(img);
    
    int height   = dims[0];
    int width    = dims[1];
    
    mxClassID input_type = mxGetClassID(img);
    
    mxArray *output = mxCreateNumericArray(ndims, dims, input_type, mxREAL);
    plhs[0] = output;
    
    // variables for A, B and I_min 
    double *A, *B, *I_min;
    A     = mxGetPr(prhs[1]); 
    B     = mxGetPr(prhs[2]);
    I_min = mxGetPr(prhs[3]);
    
    // apply processing
    if (mxIsUint8(img))
    {
        unsigned char *img_ptr = (unsigned char *)mxGetData(img);
        unsigned char *out_ptr = (unsigned char *)mxGetData(output);
        
        c_piecewise(width, height, img_ptr, out_ptr, *A, *B, *I_min);
    }   
}