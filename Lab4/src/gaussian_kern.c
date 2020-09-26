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
void adaptive_histogram(double sigma, int W, double *output)
{
    
    double kernel[W][W];
    double mean = W/2;
    double sum = 0.0; // For accumulating the kernel values
    for (int x = 0; x < W; ++x) 
        for (int y = 0; y < W; ++y) {
            kernel[x][y] = exp( -0.5 * (pow((x-mean)/sigma, 2.0) + pow((y-mean)/sigma,2.0)) )
                             / (2 * M_PI * sigma * sigma);

            // Accumulate the kernel values
            sum += kernel[x][y];
        }

    // Normalize the kernel
    for (int x = 0; x < W; ++x) 
        for (int y = 0; y < W; ++y)
            kernel[x][y] /= sum;


    for (int x = 0; x < W; ++x){ 
        for (int y = 0; y < W; ++y){
            int ind = x*W + y;
            output[ind] = kernel[x][y]; 
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
    
    if (nrhs != 2)
        mexErrMsgTxt("img_threshold can only accept three input argument");
    
    // mask dimensions
    double sig = mxGetScalar(prhs[0]); 
    int      W = mxGetScalar(prhs[1]);

    // size of kernel
    const mwSize *dims;
    
    mxArray *output = mxCreateDoubleMatrix(W, W, mxREAL);
    plhs[0] = output;
    
    // apply processing
    
    double *out_ptr = (double *)mxGetData(output);

    adaptive_histogram(sig, W, out_ptr);

       
}
