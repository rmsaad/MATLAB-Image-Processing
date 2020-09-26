/**
 * @file
 * @brief Simple mex function that computes a point operation to directly manipulate the image intensity values
 * @author Rami Saad
 * @date September 14, 2019
 *
 * Usage:
 *  >> img_out = apply_point_tfrm(img_in, C, B);
 *
 */
#include "mex.h"

/**
 * @brief Applies point transform on image of type "uint8".
 * @param[in] width
 *      the width of the image in pixels
 * @param[in] height
 *      the height of the image in pixels
 * @param[in] input
 *      pointer to the first element of the image that we're modifying
 * @param[out] output
 *      pointer to the first element of where the output image will be 
 *      stored
 * @param[in] C
 *      Scaling value for image intensity
 * @param[in] B
 *      value to be added to increase image intensity , must be a real number within range of 0 < B < 255
 */
void p_transform(int width, int height, const unsigned char *input, unsigned char *output, double C, double B){
    
     for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
        {
           int ind = x*height + y;
           
           // apply point transform
           int temp = (int)((C * input[ind]) + B);
           
           // ensure that the image intensity is within correct bounds
           if(temp > 255)
               temp = 255;
           if (temp < 0)
               temp = 0;
           
           // assign temp value to correct place in output index 
           output[ind] = temp;
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
        mexErrMsgTxt("apply_point_tfrm requires one output argument");
    
    if (nrhs != 3)
        mexErrMsgTxt("apply_point_tfrm can only accept three input argument");
    
    const mxArray *img = prhs[0];
    
    // make sure that the input arguments are the right type.
    if (!mxIsUint8(img))
        mexErrMsgTxt("apply_point_tfrm can only accept images of type 'uint8'");
    
    // extract the dimensions from the array.  
    mwSize ndims = mxGetNumberOfDimensions(img);
    const mwSize *dims = mxGetDimensions(img);
    
    int height   = dims[0];
    int width    = dims[1];
    
    // allocate storage for the output.
    mxClassID input_type = mxGetClassID(img);
    
    
    mxArray *output = mxCreateNumericArray(ndims, dims, input_type, mxREAL);
    plhs[0] = output;
    
    // variables for b and c 
    double *c, *b;
    c = mxGetPr(prhs[1]); 
    b = mxGetPr(prhs[2]);
    
    // ensure b value is within correct bounds
    if (*b < 0 || *b > 255){
        mexErrMsgTxt("B value must reside within 0 < B < 255 range!");
    }
    
    // apply processing
    if (mxIsUint8(img))
    {
        unsigned char *img_ptr = (unsigned char *)mxGetData(img);
        unsigned char *out_ptr = (unsigned char *)mxGetData(output);
        
        p_transform(width, height, img_ptr, out_ptr, *c, *b);
    }   
}