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
 * @brief Applies spatial filter on image of type "double".
 * @param[in] width
 *      the width of the image in pixels
 * @param[in] height
 *      the height of the image in pixels
 @param[in] h_height
 *      the height of the mask in pixels
 * @param[in] h_width
 *      the width of the mask in pixels
 * @param[in] input
 *      pointer to the first element of the image that we're modifying
 * @param[out] output
 *      pointer to the first element of where the output image will be 
 *      stored
 * @param[in] h
 *      mask for applying the spatial filter
 */
void s_filter(int width, int height, int h_height, int h_width, const double *input, double *output, double *h){
    int travel_h = h_height / 2;
    int travel_w = h_width  / 2;
    double temp = 0;
    
    // make sure spatial filter does not exceed input array bounds
    for (int y = floor(travel_h); y < height - floor(travel_h); y++)
        for (int x =  floor(travel_w); x < width - floor(travel_w); x++)
        {
        // calculation of specific index  
        int ind = x*height + y;
        temp = 0;
        
        // make sure spatial filter does not exceed input array bounds
        for(int i = floor(-travel_w); i <= floor(travel_w); i++)
                for (int j = floor(-travel_h); j <= floor(travel_h); j++){
                    
                    // calculation of specific index  
                    int ind_h1 = i*height + j;
                    int ind_h2 = i*h_height + j + (h_height * travel_w);
                    
                    // appy the spatial filter operation
                    temp = temp + input[ind + ind_h1] * h[ind_h2];
                    output[ind] = temp;
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
        mexErrMsgTxt("spatial_filter requires one output argument");
    
    if (nrhs != 2)
        mexErrMsgTxt("spatial_filter can only accept three input argument");
    
    const mxArray *img = prhs[0];
    const mxArray *h   = prhs[1];
    
    // make sure that the input arguments are the right type.
    if (!mxIsDouble(img))
        mexErrMsgTxt("spatial_filter can only accept images of type 'double'");
    
    // extract the dimensions from the array.  
    mwSize ndims = mxGetNumberOfDimensions(img);
    const mwSize *dims = mxGetDimensions(img);
    const mwSize *h_dims = mxGetDimensions(h);
    
    
    int height   = dims[0];
    int width    = dims[1];
    int h_height = h_dims[0];
    int h_width  = h_dims[1];
    
    // allocate storage for the output.
    mxClassID input_type = mxGetClassID(img);
    
    
    mxArray *output = mxCreateNumericArray(ndims, dims, input_type, mxREAL);
    plhs[0] = output;
    
    
    // apply processing
    if (mxIsDouble(img))
    {
        double *img_ptr = (double *)mxGetData(img);
        double *h_ptr   = (double *)mxGetData(h);
        double *out_ptr = (double *)mxGetData(output);
        
        s_filter(width, height, h_height, h_width, img_ptr, out_ptr, h_ptr);
    }   
}