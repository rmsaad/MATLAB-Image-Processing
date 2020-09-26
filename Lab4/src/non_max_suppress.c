/**
 * @file
 * @brief Simple mex function that computes a NMS Filter
 * @author Rami Saad
 * @date October 14, 2019
 *
 * Usage:
 *  >> img_out = non_max_suppress(img_in, H, W);
 *
 */
#include "mex.h"
#include <math.h>
    
/**
 * @brief Applies spatial on image of type "double".
 * @param[in] height
 *      the height of the image in pixels
  * @param[in] width
 *      the width of the image in pixels
 * @param[in] HF
 *      the size of the NMS height array
 * @param[in] WF
 *      the size of the NMS width array
 * @param[in] input
 *      pointer to the first element of the image that we're modifying
 * @param[out] output
 *      pointer to the first element of where the output image will be 
 *      stored
 * @param[in] *h
 *      NMS height filter array
 * @param[in] *w
 *      NMS height filter array
 */
void nms_filter(int height, int width, const double *input, double *output, double H_arr, double W_arr, double *temp){ 
    // variables
    int H = (int)H_arr;
    int W = (int)W_arr;
    int trv_W = W / 2;
    int trv_H = H / 2;
            
    // Height NMS filter
    for (int y = 0 ; y < height; y++)              
        for (int x = 0; x < width; x++)
        {   
            // calculation of specific index and init max value
            int ind_h = y + x*height;
            double max_H = 0;
            
            // make sure NMS does not exceed input array bounds
            // Calc Height NMS
            if (((ind_h + trv_H*height) < (width)*(height))&& (ind_h) >= trv_H*height){
                for (int i = (ind_h - trv_H*height); i <= (ind_h + trv_H*height); i = i+height){
                    if (input[i] >= max_H){
                        max_H = input[i];
                    }
                }
            }
            
            // store results
            if (input[ind_h] == max_H){
                temp[ind_h] = input[ind_h];
            }else{
                temp[ind_h] = 0;
            }
             

        }
        
        // Width NMS filter
        for (int y = 0 ; y < height; y++)              
        for (int x = 0; x < width; x++)
        {   
            // calculation of specific index and max value
            int ind_x = x + y*width;
            double max_W = 0;
            
            // make sure NMS does not exceed input array bounds
            // Calc Width NMS
            if (((ind_x + trv_W) < (width)*(height)) && (ind_x - trv_W) >= 0){
                for (int i = (ind_x - trv_W); i <= (ind_x + trv_W); i++){
                    if (temp[i] >= max_W){
                        max_W = temp[i];
                    }
                }
            }
            
            // store results
            if (temp[ind_x] == max_W){
                output[ind_x] = temp[ind_x];
            }else{
                output[ind_x] = 0;
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
        mexErrMsgTxt("NMS_filter requires one output argument");
    
    if (nrhs != 3)
        mexErrMsgTxt("NMS_filter can only accept three input argument");
    
    const mxArray *img = prhs[0];
    
    // make sure that the input arguments are the right type.
    if (!mxIsDouble(img))
        mexErrMsgTxt("NMS_filter can only accept images of type 'double'");
    
    // extract the dimensions from the array.  
    mwSize ndims = mxGetNumberOfDimensions(img);
    const mwSize *dims = mxGetDimensions(img);
    
    int height   = dims[0];
    int width    = dims[1];
    
    // allocate storage for the output.
    mxClassID input_type = mxGetClassID(img);
    
    
    mxArray *output = mxCreateNumericArray(ndims, dims, input_type, mxREAL);
    mxArray *temp = mxCreateNumericArray(ndims, dims, input_type, mxREAL);
    plhs[0] = output;
    
     // variables for rmin and rmax
    double *H, *W;
    H = mxGetPr(prhs[1]); 
    W = mxGetPr(prhs[2]);
    
    // apply processing
    if (mxIsDouble(img))
    {
        double *img_ptr = (double *)mxGetData(img);
        double *out_ptr = (double *)mxGetData(output);
        double *temp_ptr = (double *)mxGetData(temp);
        
        nms_filter(width, height, img_ptr, out_ptr, *H, *W, temp_ptr);
    }   
}