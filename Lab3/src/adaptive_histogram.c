/**
 * @file
 * @brief Simple mex function that computes a local histogram equalization
 * @author Rami Saad
 * @date November 1, 2019
 *
 * Usage:
 *  >> img_out = adaptive_histogram(img_in, H, W);
 *
 */
#include "mex.h"
#include <math.h>

/**
 * @brief Applies spatial on img of type "double".
 * @param[in] width
 *      the width of the img in pixels
 * @param[in] height
 *      the height of the img in pixels
 * @param[in] input
 *      pointer to the first element of the img that we're modifying
 * @param[out] output
 *      pointer to the first element of where the output img will be 
 *      stored
 * @param[in] T
 *      cutoff Threshold
 */
void adaptive_histogram(int width, int height,int h_width, int h_height, const unsigned char *input ,unsigned char *output)
{
    int travel_h = h_height / 2;
    int travel_w = h_width  / 2;
    double size = (double)(h_height * h_width);
    int r_count[255] = {0};
    double cdf[255] = {0};
    int test = 0;
    
    // make sure spatial filter does not exceed input array bounds
    for (int y = floor(travel_h); y < height - floor(travel_h); y++)
        for (int x =  floor(travel_w); x < width - floor(travel_w); x++)
        {
            
        // calculation of specific index  
        int ind = x*height + y;
   
        // make sure spatial filter does not exceed input array bounds
        for(int i = floor(-travel_w); i <= floor(travel_w); i++)
                for (int j = floor(-travel_h); j <= floor(travel_h); j++){
                    
                    // calculation of specific index  
                    int ind_h1 = i*height + j;
                    int ind_h2 = i*h_height + j + (h_height * travel_w);
                    
                    // appy the spatial filter operation
                    r_count[input[ind + ind_h1]]++;                  
                }
        
        // calculate probabilty
        for (int q = 0; q < 255; q++){
            cdf[q] = (double)r_count[q] / size; 
        }
        
        // caclulate cdf
        for (int w = 0; w < 255; w++){
            if (w != 0){
            cdf[w] = cdf[w] + cdf[w - 1];
            }
        }
       
        // multiply by 255 and convert to int
        for (int e = 0; e < 255; e++){
            cdf[e] = cdf[e] * 255.0;
            r_count[e] = (int)cdf[e];

        }

        output[ind] =  r_count[input[ind]];

        for (int q = 0; q < 255; q++){
            r_count[q] = 0;
            cdf[q] = 0;
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
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    // check that the number of input and output arguments are correct and 
    // otherwise mex function will crash and display an error message
    if (nlhs != 1)
        mexErrMsgTxt("img_threshold requires one output argument");
    
    if (nrhs != 3)
        mexErrMsgTxt("img_threshold can only accept three input argument");
    
    const mxArray *img = prhs[0];
    
    // mask dimensions
    int loc_h = mxGetScalar(prhs[1]); 
    int loc_w = mxGetScalar(prhs[2]);
    	
    if (!mxIsUint8(img)) 
		mexErrMsgTxt("function can only accept imgs of type 'uint8'");
    
    // extract the dimensions from the array.
    mwSize ndims = mxGetNumberOfDimensions(img);
    const mwSize *dims = mxGetDimensions(img);
    
    int height   = dims[0];
    int width    = dims[1];
    
    // allocate storage for the output. 
    mxClassID input_type = mxGetClassID(img);
    
    
    mxArray *output = mxCreateNumericArray(ndims, dims, input_type, mxREAL);
    plhs[0] = output;
    
    // apply processing
    if (mxIsUint8(img))
    {
        unsigned char *img_ptr = (unsigned char *)mxGetData(img);
        unsigned char *out_ptr = (unsigned char *)mxGetData(output);

        adaptive_histogram(width, height, loc_w, loc_h, img_ptr,out_ptr);

    }   
}
