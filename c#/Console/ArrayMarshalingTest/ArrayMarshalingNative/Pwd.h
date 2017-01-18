// 2017-01-18T09:37:25+08:00
#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef PWD_API
# define PWD_API __declspec(dllimport)
#endif

PWD_API char *GetCurrentDirectory(char *buf, int len);

#ifdef __cplusplus
}
#endif