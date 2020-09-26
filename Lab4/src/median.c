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
#include <stdlib.h>

int cmpfunc (const void * a, const void * b)
{
  if (*(double*)a > *(double*)b)
    return 1;
  else if (*(double*)a < *(double*)b)
    return -1;
  else
    return 0;  
}

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
void s_filter(int width, int height, const double *input, double *output, int WW, int HH){
    int W = (int)WW;
    int H = (int)HH;
    int travel_h = H / 2;
    int travel_w = W / 2;
    double temp[W*H];
    
    // make sure spatial filter does not exceed input array bounds
    for (int y = floor(travel_h); y < height - floor(travel_h); y++)
        for (int x =  floor(travel_w); x < width - floor(travel_w); x++)
        {
        // calculation of specific index  
        int ind = x*height + y;
        int k = 0;
        // make sure spatial filter does not exceed input array bounds
        for(int i = floor(-travel_w); i <= floor(travel_w); i++)
                for (int j = floor(-travel_h); j <= floor(travel_h); j++){
                    
                    // calculation of specific index  
                    int ind_h1 = i * height + j;
                    int ind_h2 = i * H + j + (H * W);
                   
                    temp[k] = input[ind + ind_h1];
                    k++;
                }
            
            qsort(temp, H*W, sizeof(double), cmpfunc);
        
            for (int j = 0; j < H*W; j++)
            {
               //printf("%lf ", temp[j]); 
            }
             //printf("  ");
        output[ind] = temp[(W*H-1)/2];
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
    
    if (nrhs != 3)
        mexErrMsgTxt("spatial_filter can only accept three input argument");
    
    const mxArray *img = prhs[0];
    
    // make sure that the input arguments are the right type.
    if (!mxIsDouble(img))
        mexErrMsgTxt("spatial_filter can only accept images of type 'double'");
    
    // extract the dimensions from the array.  
    mwSize ndims = mxGetNumberOfDimensions(img);
    const mwSize *dims = mxGetDimensions(img);
    
    
    int height   = dims[0];
    int width    = dims[1];
    
    // allocate storage for the output.
    mxClassID input_type = mxGetClassID(img);
    
    
    mxArray *output = mxCreateNumericArray(ndims, dims, input_type, mxREAL);
    plhs[0] = output;
    
    double *W;
    W = mxGetPr(prhs[1]);
    
    double *H;
    H = mxGetPr(prhs[2]);
    
    // apply processing
    if (mxIsDouble(img))
    {
        double *img_ptr = (double *)mxGetData(img);
        double *out_ptr = (double *)mxGetData(output);
        
        s_filter(width, height, img_ptr, out_ptr, *W, *H);
    }   
}