// 2016-03-25T11:28+08:00
#ifndef DATA_SEQ_H_
#define DATA_SEQ_H_

#include <stdio.h>

#ifndef DATASEQ_API
# ifndef SWIG
#  define DATASEQ_API __declspec(dllimport)
# else
#  define DATASEQ_API // Ongoing-study/python/SWIG/DataSeq/DataSeq.i
# endif
#endif


#ifdef __cplusplus
extern "C" {
#endif

// Instead of what we do in DataSequence.h:
//     typedef void *DataSequence;
// we use a pointer of an incomplete type as the data sequence *handle* in this
// version. The benefit is obversely:
// 1. Improved type safety;
// 2. In DataSeq.cpp, there is no need to cast DataSeq * to a pointer of some
//    internal type(as what we did in DataSequence.cpp);
// This is inspired by the C implementation of SQLite3.
//
typedef struct DataSeq *DataSeqHandle;
typedef unsigned int    Size;

typedef enum {
    NoError          = 0,
    IndexOutOfRange  = 1,
    InvalidParameter = 2,
    InvalidOperation = 3,
    MemoryError      = 4,
    UnknownError     = 5,
} Error;


DATASEQ_API Error DataSeq_Create(DataSeqHandle *dataSeqPtr, Size size);
DATASEQ_API Error DataSeq_PushBack(DataSeqHandle dataSeq, double v);
DATASEQ_API Error DataSeq_PopBack(DataSeqHandle dataSeq, double *v);
DATASEQ_API Error DataSeq_GetSize(DataSeqHandle dataSeq, Size *size);
DATASEQ_API Error DataSeq_GetAt(DataSeqHandle dataSeq, Size i, double *v);
DATASEQ_API Error DataSeq_SetAt(DataSeqHandle dataSeq, Size i, double v);
DATASEQ_API Error DataSeq_GetData(DataSeqHandle dataSeq, double **pData);
DATASEQ_API Error DataSeq_Dump(DataSeqHandle dataSeq, FILE *stream);
DATASEQ_API void  DataSeq_Free(DataSeqHandle dataSeq);

DATASEQ_API DataSeqHandle DataSeq_CreateV2(Size size);
DATASEQ_API Size DataSeq_GetSizeV2(DataSeqHandle dataSeq);
DATASEQ_API double *DataSeq_GetDataV2(DataSeqHandle dataSeq);

#ifdef __cplusplus
}
#endif

#endif // DATA_SEQ_H_

// References:
// https://www.zhihu.com/question/41106231
// http://www.codeproject.com/Articles/28969/HowTo-Export-C-classes-from-a-DLL