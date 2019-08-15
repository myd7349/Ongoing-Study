#ifndef ASSERT_IMPL_H_
#define ASSERT_IMPL_H_

#ifndef FUNCTION_NAME
# ifdef _MSC_VER
#  define FUNCTION_NAME __FUNCTION__  
# else
#  define FUNCTION_NAME __func__ 
# endif
#endif

#define xverify(expr) (void)((!!(expr)) || (assert_impl(__FILE__, __LINE__, FUNCTION_NAME, #expr), 0))

#ifdef NDEBUG
# define xassert(expr) ((void)0)
#else
# define xassert(expr) xverify(expr)
#endif

#ifdef __cplusplus
extern "C"
{
#endif

void assert_impl(const char *file, int line, const char *func, const char *expr);

#ifdef __cplusplus
}
#endif

#endif // ASSERT_IMPL_H_


// References:
// https://stackoverflow.com/questions/15305310/predefined-macros-for-function-name-func
// https://github.com/jedisct1/libhydrogen/issues/71
