#include "filter.h"

#include <algorithm>
#include <cassert>
#include <new>


Filter::Filter(int bufferLength)
{
    if (bufferLength_ > 0)
    {
        bufferLength_ = bufferLength;
        buffer_ = new (std::nothrow) double[bufferLength];
        sortedBuffer_ = new (std::nothrow) double[bufferLength];
    }
}

Filter::~Filter()
{
    delete[] buffer_;
    delete[] sortedBuffer_;
}

double Filter::Run(double v)
{
    if (bufferLength_ <= 0)
        return v;

    for (int i = 1; i < bufferLength_; ++i)
        buffer_[i - 1] = buffer_[i];
    buffer_[bufferLength_ - 1] = v;

    std::copy(buffer_, buffer_ + bufferLength_, sortedBuffer_);
    std::sort(sortedBuffer_, sortedBuffer_ + bufferLength_);

    return sortedBuffer_[bufferLength_ / 2];
}