// 2016-03-16T12:25+08:00
#ifndef DATA_SEQUENCE_H_
#define DATA_SEQUENCE_H_

#include <stdio.h>

#ifndef DATASEQ_API
# define DATASEQ_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef void *       DataSequence;
typedef unsigned int Size;

typedef enum {
    NoError          = 0,
    IndexOutOfRange  = 1,
    InvalidParameter = 2,
    InvalidOperation = 3,
    MemoryError      = 4,
    UnknownError     = 5,
} Error;

#define INVALID_SIZE ((Size)-1)

DATASEQ_API Error DataSeq_Create(DataSequence *dataSeqPtr, Size size);
DATASEQ_API Error DataSeq_PushBack(DataSequence dataSeq, double v);
DATASEQ_API Error DataSeq_PopBack(DataSequence dataSeq, double *v);
DATASEQ_API Error DataSeq_GetSize(DataSequence dataSeq, Size *size);
DATASEQ_API Error DataSeq_GetAt(DataSequence dataSeq, Size i, double *v);
DATASEQ_API Error DataSeq_SetAt(DataSequence dataSeq, Size i, double v);
DATASEQ_API Error DataSeq_GetData(DataSequence dataSeq, const double **pData);
DATASEQ_API Error DataSeq_Dump(DataSequence dataSeq, FILE *stream);
DATASEQ_API void  DataSeq_Free(DataSequence dataSeq);

#ifdef __cplusplus
}
#endif

#endif // DATA_SEQUENCE_H_
