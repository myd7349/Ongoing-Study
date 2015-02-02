// 2015-02-02T15:06+08:00

#ifndef DIVIDING_LINES_H_
#define DIVIDING_LINES_H_

#include <iostream>
#include <string>

#include "common.h"
#include "variadic_macro.h"

#define DIVIDING_LINE_2(c, n) ((void)(std::cout << std::string(n, c) << std::endl))
#define DIVIDING_LINE_1(c) DIVIDING_LINE_2(c, 79)
//#define DIVIDING_LINE_0() DIVIDING_LINE_1('-')

//#include <boost/preprocessor.hpp>
//#define DIVIDING_LINE(...) BOOST_PP_OVERLOAD(DIVIDING_LINE_, __VA_ARGS__)(__VA_ARGS__)

#if defined(_MSC_VER)
# define SELMACRO_IMPL(_1, _2, N, ...) N
# define SELMACRO_IMPL_(tuple) SELMACRO_IMPL tuple
# define DIVIDING_LINE(...) SELMACRO_IMPL_((__VA_ARGS__, DIVIDING_LINE_2(__VA_ARGS__), DIVIDING_LINE_1(__VA_ARGS__)))
#elif defined(__GNUC__) || defined(__GNUG__)
# define DIVIDING_LINE(...) CONCAT(DIVIDING_LINE_, VA_NARGS_V2(__VA_ARGS__))(__VA_ARGS__)
#else
# error Not tested yet!
#endif


#endif // DIVIDING_LINES_H_

// References:
// [Can C/C++ preprocessor macros have default parameter values?](http://stackoverflow.com/questions/27049491/can-c-c-preprocessor-macros-have-default-parameter-values)
// [Optional Parameters with C++ Macros](http://stackoverflow.com/questions/3046889/optional-parameters-with-c-macros)
//
