/**
 * @file
 * @brief Simple mex function that computes a histogram equalization
 * @author Rami Saad
 * @date November 1, 2019
 *
 * Usage:
 *  >> img_out = histogram_equalize(img_in);
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
 */
void histogram_equalize(int height, int width, const unsigned char *input, unsigned char *output)
{
    double size = (double)(height * width);
    int r_count[255] = {0};
    double cdf[255] = {0};
    
    // count intensity values
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
        {
            int ind = x*height + y;
            r_count[input[ind]]++;        
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
    
    // now equalize the intesity values
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
        {
            int ind = x*height + y;
            output[ind] = r_count[input[ind]];        
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
    
    if (nrhs != 1)
        mexErrMsgTxt("img_threshold can only accept one input argument");

	const mxArray *img = prhs[0];
	
	if (!mxIsUint8(img)) 
		mexErrMsgTxt("function can only accept imgs of type 'uint8'");

	// extract the dimensions from the array.
    mwSize ndims = mxGetNumberOfDimensions(img);
    const mwSize *dims = mxGetDimensions(img);
    
    int height   = dims[0];
    int width    = dims[1];
    
    // allocate storage for the output.
    mxClassID input_type = mxGetClassID(img);
    
    mxArray *output = mxCreateNumericArray(ndims, dims,input_type, mxREAL);
	plhs[0] = output;
	
    // apply processing
    if (mxIsUint8(img))
    {
        unsigned char *img_ptr = (unsigned char *)mxGetData(img);
        unsigned char *out_ptr = (unsigned char *)mxGetData(output);

        histogram_equalize(height, width, img_ptr,out_ptr);

    }   
}