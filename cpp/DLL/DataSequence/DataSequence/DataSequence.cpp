#define DATASEQ_API __declspec(dllexport)
#include "DataSequence.h"
#include "DataSequencePrivate.h"

#include <cassert>
#include <cstdio>
#include <new>
#include <stdexcept>


Error DataSeq_Create(DataSequence *dataSeqPtr, Size size)
{
    assert(dataSeqPtr != nullptr && size != INVALID_SIZE);
    if (nullptr == dataSeqPtr || INVALID_SIZE == size)
        return InvalidParameter;

    if (*dataSeqPtr != nullptr)
        DataSeq_Free(*dataSeqPtr);

    DataSequenceImpl *dataSeq = nullptr;
    try {
        dataSeq = new DataSequenceImpl(size);
    } catch (const std::bad_alloc &) {
        return MemoryError;
    }

    *dataSeqPtr = static_cast<DataSequence>(dataSeq);

    return NoError;
}

Error DataSeq_PushBack(DataSequence dataSeq, double v)
{
    assert(dataSeq != nullptr);
    if (nullptr == dataSeq)
        return InvalidParameter;

    DataSequenceImpl *dataSeqImpl = static_cast<DataSequenceImpl *>(dataSeq);
    dataSeqImpl->push_back(v);

    return NoError;
}

Error DataSeq_PopBack(DataSequence dataSeq, double *v)
{
    assert(dataSeq != nullptr);
    if (nullptr == dataSeq)
        return InvalidParameter;

    DataSequenceImpl *dataSeqImpl = static_cast<DataSequenceImpl *>(dataSeq);
    if (v != nullptr)
        *v = dataSeqImpl->back();
    dataSeqImpl->pop_back();

    return NoError;
}

Error DataSeq_Size(DataSequence dataSeq, Size *size)
{
    assert(dataSeq != nullptr && size != nullptr);
    if (nullptr == dataSeq || nullptr == size)
        return InvalidParameter;

    *size = static_cast<DataSequenceImpl *>(dataSeq)->size();

    return NoError;
}

Error DataSeq_GetAt(DataSequence dataSeq, Size i, double *v)
{
    assert(dataSeq != nullptr && v != nullptr);
    if (nullptr == dataSeq || nullptr == v)
        return InvalidParameter;

    try {
        *v = static_cast<DataSequenceImpl *>(dataSeq)->at(i);
        return NoError;
    } catch (const std::out_of_range &) {
        return IndexOutOfRange;
    }
}

Error DataSeq_SetAt(DataSequence dataSeq, Size i, double v)
{
    assert(dataSeq != nullptr);
    if (nullptr == dataSeq)
        return InvalidParameter;

    Size size;
    if (Error error = DataSeq_Size(dataSeq, &size))
        return error;

    if (i >= size)
        return IndexOutOfRange;

    (*static_cast<DataSequenceImpl *>(dataSeq))[i] = v;

    return NoError;
}

Error DataSeq_Data(DataSequence dataSeq, const double **pData)
{
    assert(dataSeq != nullptr && pData != nullptr);
    if (nullptr == dataSeq || nullptr == pData)
        return InvalidParameter;

    *pData = static_cast<DataSequenceImpl *>(dataSeq)->data();

    return NoError;
}

Error DataSeq_Dump(DataSequence dataSeq, FILE *stream)
{
    assert(dataSeq != nullptr && stream != nullptr);
    if (nullptr == dataSeq || nullptr == stream)
        return InvalidParameter;

    Size size;
    if (Error error = DataSeq_Size(dataSeq, &size))
        return error;

    if (0 == size)
        return NoError;

    DataSequenceImpl &dataSeqRef = *static_cast<DataSequenceImpl *>(dataSeq);

    fprintf(stream, "[%.2f", dataSeqRef[0]);
    for (Size i = 1; i < size; ++i)
        fprintf(stream, ", %.2f", dataSeqRef[i]);
    fputs("]\n", stream);

    return NoError;
}

void DataSeq_Free(DataSequence dataSeq)
{
    assert(dataSeq != nullptr);
    if (dataSeq != nullptr) {
        DataSequenceImpl *dataSeqImpl = static_cast<DataSequenceImpl *>(dataSeq);
        delete dataSeqImpl;
    }
}