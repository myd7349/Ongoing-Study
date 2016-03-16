// 2016-03-16T12:25+08:00
// DataSequence is implemented with C++, but exposes a C style API.
// This sample is inspired by libzmq.

#include "../DataSequence/DataSequence.h"
#include "../../../common.h"

#include <assert.h>
#include <stdio.h>


int main()
{
    DataSequence dataSeq = NULL;
    Error error = NoError;
    Size size = 0;
    double v = 0.0;

    error = DataSeq_Create(&dataSeq, 0);
    if (error) {
        fprintf(stdout, "Failed to create data sequence.\n");
        return 1;
    }

    // push back test
    error = DataSeq_PushBack(dataSeq, 1.0);
    assert(NoError == error);
    error = DataSeq_PushBack(dataSeq, 3.14);
    assert(NoError == error);
    error = DataSeq_PushBack(dataSeq, 2.0);
    assert(NoError == error);

    // dump test
    error = DataSeq_Dump(dataSeq, stdout);
    assert(NoError == error);

    // size
    error = DataSeq_Size(dataSeq, &size);
    assert(NoError == error);
    if (NoError == error)
        fprintf(stdout, "Current size: %u\n", size);

    // pop back test
    error = DataSeq_PopBack(dataSeq, &v);
    assert(NoError == error);
    if (NoError == error)
        fprintf(stdout, "Pop back: %f\n", v);

    // dump test
    error = DataSeq_Dump(dataSeq, stdout);
    assert(NoError == error);

    // set at
    // -- index out of range
    error = DataSeq_SetAt(dataSeq, 2, 100);
    assert(IndexOutOfRange == error);
    error = DataSeq_SetAt(dataSeq, 1, 100);
    assert(NoError == error);

    // dump test
    error = DataSeq_Dump(dataSeq, stdout);
    assert(NoError == error);

    // get at
    error = DataSeq_GetAt(dataSeq, 1, &v);
    assert(NoError == error);
    if (NoError == error)
        fprintf(stdout, "%f\n", v);

    // data
    const double *pData = NULL;
    error = DataSeq_Data(dataSeq, &pData);
    assert(NoError == error && pData != NULL);

    // free
    DataSeq_Free(dataSeq);

    PAUSE();
    return 0;
}