// 2017-08-16T12:23+08:00
// mex: Call C/C++ functions from MATLAB. 
// mcc: Compile MATLAB functions for deployment.
// You can build C/C++ extension for MATLAB with mex. This is an example.

/*
>> mex primeFactors.cpp
>> primeFactors(4)

ans =

     2     2

>> factors = primeFactors(10)

factors =

     2     5
*/

#include <algorithm>
#include <list>


std::list<int> primeFactors(int n) {
    std::list<int> factors;

    for (int candidate = 2; n > 1; ++candidate) {
        for (; n % candidate == 0; n /= candidate) {
            factors.push_back(candidate);
        }
    }

    return factors;
}


#include "mex.h"



void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs != 1) {
        mexErrMsgTxt("One input required.");
    }

    if (!mxIsDouble(prhs[0]) ||
        mxIsComplex(prhs[0]) ||
        mxGetNumberOfElements(prhs[0]) != 1) {
        mexErrMsgTxt("Input upper-bound must be a scalar.");
    }

    if (nlhs != 0 && // `ans` 
        nlhs != 1) {
        mexErrMsgTxt("One output required.");
    }

    int n = (int)mxGetScalar(prhs[0]);
    if (n <= 0) {
        mexErrMsgTxt("The input should be non-negative.");
    }

    std::list<int> factors = primeFactors(n);

    plhs[0] = mxCreateDoubleMatrix(1, (mwSize)factors.size(), mxREAL);
    double *outMatrix = mxGetPr(plhs[0]);

    std::copy(factors.cbegin(), factors.cend(), outMatrix);
}

// References:
// doc mex
// doc factors
// [Return variable number of outputs from mex function](https://stackoverflow.com/questions/26460963/return-variable-number-of-outputs-from-mex-function)
// http://pages.cs.wisc.edu/~ferris/cs733/Seminarium_CBA_ht07_MATLAB_MEX_handouts.pdf
// http://101.96.8.164/www.cosy.sbg.ac.at/%7Euhl/C-matlab.pdf
