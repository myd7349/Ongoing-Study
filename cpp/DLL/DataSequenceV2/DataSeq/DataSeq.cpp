#define DATASEQ_API __declspec(dllexport)
#include "DataSeq.h"

#include <cassert>
#include <cstdio>
#include <new>
#include <stdexcept>
#include <vector>

struct DataSeq {
    std::vector<double> data;
};

const Size INVALID_SIZE = ((Size)-1);


Error DataSeq_Create(DataSeqHandle *dataSeqPtr, Size size)
{
    assert(dataSeqPtr != nullptr && size != INVALID_SIZE);
    if (nullptr == dataSeqPtr || INVALID_SIZE == size)
        return InvalidParameter;

    if (*dataSeqPtr != nullptr)
        DataSeq_Free(*dataSeqPtr);

    try {
        *dataSeqPtr = new DataSeq();
        (*dataSeqPtr)->data.resize(size);
    } catch (const std::bad_alloc &) {
        return MemoryError;
    }

    return NoError;
}

Error DataSeq_PushBack(DataSeqHandle dataSeq, double v)
{
    assert(dataSeq != nullptr);
    if (nullptr == dataSeq)
        return InvalidParameter;

    dataSeq->data.push_back(v);

    return NoError;
}

Error DataSeq_PopBack(DataSeqHandle dataSeq, double *v)
{
    assert(dataSeq != nullptr);
    if (nullptr == dataSeq)
        return InvalidParameter;

    auto &data = dataSeq->data;
    if (data.empty())
        return InvalidOperation;

    if (v != nullptr)
        *v = data.back();
    data.pop_back();

    return NoError;
}

Error DataSeq_GetSize(DataSeqHandle dataSeq, Size *size)
{
    assert(dataSeq != nullptr && size != nullptr);
    if (nullptr == dataSeq || nullptr == size)
        return InvalidParameter;

    *size = dataSeq->data.size();

    return NoError;
}

Error DataSeq_GetAt(DataSeqHandle dataSeq, Size i, double *v)
{
    assert(dataSeq != nullptr && v != nullptr);
    if (nullptr == dataSeq || nullptr == v)
        return InvalidParameter;

    try {
        *v = dataSeq->data.at(i);
        return NoError;
    } catch (const std::out_of_range &) {
        return IndexOutOfRange;
    }
}

Error DataSeq_SetAt(DataSeqHandle dataSeq, Size i, double v)
{
    assert(dataSeq != nullptr);
    if (nullptr == dataSeq)
        return InvalidParameter;

    Size size;
    if (Error error = DataSeq_GetSize(dataSeq, &size))
        return error;

    if (i >= size)
        return IndexOutOfRange;

    dataSeq->data[i] = v;

    return NoError;
}

Error DataSeq_GetData(DataSeqHandle dataSeq, double **pData)
{
    assert(dataSeq != nullptr && pData != nullptr);
    if (nullptr == dataSeq || nullptr == pData)
        return InvalidParameter;

    *pData = dataSeq->data.data();

    return NoError;
}

Error DataSeq_Dump(DataSeqHandle dataSeq, FILE *stream)
{
    assert(dataSeq != nullptr && stream != nullptr);
    if (nullptr == dataSeq || nullptr == stream)
        return InvalidParameter;

    Size size;
    if (Error error = DataSeq_GetSize(dataSeq, &size))
        return error;

    if (0 == size)
        return NoError;

    auto &data = dataSeq->data;
    fprintf(stream, "[%.2f", data[0]);
    for (Size i = 1; i < size; ++i)
        fprintf(stream, ", %.2f", data[i]);
    fputs("]\n", stream);

    return NoError;
}

void DataSeq_Free(DataSeqHandle dataSeq)
{
    assert(dataSeq != nullptr);
    if (dataSeq != nullptr) {
        delete dataSeq;
    }
}


DataSeqHandle DataSeq_CreateV2(Size size)
{
    assert(size != INVALID_SIZE);
    if (INVALID_SIZE == size)
        return nullptr;

    DataSeqHandle dataSeq = nullptr;

    try {
        dataSeq = new DataSeq();
        dataSeq->data.resize(size);
    } catch (const std::bad_alloc &) {
        return nullptr;
    }

    return dataSeq;
}

Size DataSeq_GetSizeV2(DataSeqHandle dataSeq)
{
    assert(dataSeq != nullptr);
    if (nullptr == dataSeq)
        return INVALID_SIZE;

    return dataSeq->data.size();
}

double *DataSeq_GetDataV2(DataSeqHandle dataSeq)
{
    assert(dataSeq != nullptr);
    if (nullptr == dataSeq)
        return nullptr;

    return dataSeq->data.data();
}