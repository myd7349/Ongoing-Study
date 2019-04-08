#pragma once

#ifdef _MSC_VER
# ifdef LIBRDKAFKA_STATICLIB
#  define RD_EXPORT
# else
#  ifdef LIBRDKAFKACPP_EXPORTS
#   define RD_EXPORT __declspec(dllexport)
#  else
#   define RD_EXPORT __declspec(dllimport)
#  endif
# endif
#else
# define RD_EXPORT
#endif

class RD_EXPORT Foo
{
public:
    static void hello();
    
    static const int BAR;
};


#define FOO_STR_IMPL(c) #c
#define FOO_STR(c) FOO_STR_IMPL(c)


RD_EXPORT extern int version;


// References:
// https://github.com/edenhill/librdkafka/blob/master/src-cpp/rdkafkacpp.h
// https://github.com/edenhill/librdkafka/pull/2274
