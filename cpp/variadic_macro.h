// 2015-02-02T13:17+08:00

#ifndef VARIADIC_MACRO_H_
#define VARIADIC_MACRO_H_

// VA_NARGS: Yet another BOOST_PP_VARIADIC_SIZE.
// TODO: Implement this macro by using C++11's variadic template.
#define VA_NARGS_IMPL(_10, _9, _8, _7, _6, _5, _4, _3, _2, _1, N, ...) (N)

#if defined(_MSC_VER)
# define VA_NARGS_HELPER(arg_tuple) VA_NARGS_IMPL arg_tuple
# define VA_NARGS(...) (bool(#__VA_ARGS__) ? (VA_NARGS_HELPER((__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1))) : 0)
#elif defined(__GNUC__) || defined(__GNUG__)
# define VA_NARGS(...) (sizeof(#__VA_ARGS__) == 1 ? 0 : VA_NARGS_IMPL(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)) // ???
#else
# error Not tested yet!
#endif

#endif // VARIADIC_MACRO_H_

// References:
// [Can C/C++ preprocessor macros have default parameter values?](http://stackoverflow.com/questions/27049491/can-c-c-preprocessor-macros-have-default-parameter-values)
// [How to make a variadic macro (variable number of arguments)](http://stackoverflow.com/questions/679979/how-to-make-a-variadic-macro-variable-number-of-arguments)
// [Optional Parameters with C++ Macros](http://stackoverflow.com/questions/3046889/optional-parameters-with-c-macros)
// 
