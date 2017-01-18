// 2016-07-01T09:15+08:00
#ifndef FILL_STRUCT_H_
#define FILL_STRUCT_H_

#include <stdlib.h>


#ifndef FILL_STRUCT_EXPORTS
# define FILL_STRUCT_API __declspec(dllimport)
#else
# define FILL_STRUCT_API __declspec(dllexport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct Data
{
    int header;
    int data[10];
};

FILL_STRUCT_API void FillStruct(struct Data *data);

struct Cwd
{
    char cwd[_MAX_PATH];
};

FILL_STRUCT_API void GetCwd(struct Cwd *cwd);

#ifdef __cplusplus
}
#endif

#endif // FILL_STRUCT_H_
