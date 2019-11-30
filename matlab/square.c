// 2019-11-08T18:23+08:00
/*
>> mex square.c square_impl.c
>> square(1000)

ans =

     1000000

>> x = square(10)

x =

   100
*/


#include <mex.h>

#include "square_impl.h"


void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    double x;
    double *result = NULL;

    if (nrhs != 1) {
        mexErrMsgTxt("One input required.");
    }

    if (!mxIsDouble(prhs[0]) ||
        mxIsComplex(prhs[0]) ||
        mxGetNumberOfElements(prhs[0]) != 1) {
        mexErrMsgTxt("Input argument must be a scalar.");
    }

    if (nlhs != 0 && // `ans` 
        nlhs != 1) {
        mexErrMsgTxt("One output required.");
    }

    x = (double)mxGetScalar(prhs[0]);

    plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);
    result = mxGetPr(plhs[0]);

    *result = Square(x);
}

// References:
// doc mex
// mex examples: mexcpp.cpp
// http://matlab.izmiran.ru/help/techdoc/matlab_external/ch04cre5.html
// https://stackoverflow.com/questions/25167867/passing-integer-types-to-a-mex-function
