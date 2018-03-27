// 2018-03-27T10:09+08:00
#pragma once

#include <stddef.h>


#ifdef __cplusplus
extern "C"
{
#endif

#ifndef DATACHUNK_API
# define DATACHUNK_API __declspec(dllimport)
#endif

DATACHUNK_API void ProcessDataChunk(double array[], size_t len);

#ifdef __cplusplus
}
#endif
