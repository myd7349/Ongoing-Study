// 2016-08-07T19:37+08:00
#ifndef VARARGS_TEST_H_
#define VARARGS_TEST_H_

#include <cstdint>
#include <vector>

bool RetrieveASamplingFromMultiLeadsData(std::vector<int> &aSampling, unsigned pos, unsigned dataLength, const  int *lead0, ...);

#endif
