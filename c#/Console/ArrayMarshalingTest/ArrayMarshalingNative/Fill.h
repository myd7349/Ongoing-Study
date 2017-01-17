// 2017-01-17T13:16:36+08:00
#pragma once

#include <stddef.h>


#ifdef __cplusplus
extern "C"
{
#endif

#ifndef FILL_API
# define FILL_API __declspec(dllimport)
#endif

FILL_API void Fill(double array[], size_t len);

#ifdef __cplusplus
}
#endif
