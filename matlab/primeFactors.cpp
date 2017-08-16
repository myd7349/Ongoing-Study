// 2017-08-16T12:23+08:00
// mex primeFactors.cpp

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

    if (nlhs != 1) {
        mexErrMsgTxt("One output required.");
    }

    int n = (int)mxGetScalar(prhs[0]);
    std::list<int> factors = primeFactors(n);

    plhs[0] = mxCreateDoubleMatrix(1, (mwSize)factors.size(), mxREAL);
    double *outMatrix = mxGetPr(plhs[0]);

    std::copy(factors.cbegin(), factors.cend(), outMatrix);
}

// References:
// doc mex
// doc factors
