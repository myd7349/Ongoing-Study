// 2017-04-28T19:16+08:00
#ifndef DATA_SPAN_HPP_
#define DATA_SPAN_HPP_

#include <algorithm>
#include <cassert>
#include <vector>


class DataSpan
{
public:
    DataSpan()
    {
        data_ = nullptr;
        offset_ = 0;
        count_ = 0;
    }

    DataSpan(const double *data, int dataLength, int offset, int count)
    {
        assert(data != nullptr);
        assert(dataLength >= 0);
        assert(offset >= 0);
        assert(count >= 0);

        data_ = data;
        offset_ = offset;
        count_ = std::min<int>(count, dataLength - offset);
    }

    DataSpan(const double **data, int leadCount, int dataLength, int offset, int count, int id)
    {
        assert(data != nullptr);
        assert(leadCount > 0);
        assert(id >= 0 && id < leadCount);
        new (this) DataSpan(data[id], dataLength, offset, count);
    }

    DataSpan(const std::vector<double> &data, int offset, int count)
        : DataSpan(data.data(), static_cast<int>(data.size()), offset, count)
    {
    }

    const double *GetData() const
    {
        return data_ + offset_;
    }

    int GetLength() const
    {
        return count_;
    }

    bool IsEmpty() const
    {
        return data_ == nullptr || count_ == 0;
    }

    double operator[](int index) const
    {
        assert(data_ != nullptr);
        assert(index >= 0 && index < count_);
        return data_[offset_ + index];
    }

private:
    const double *data_;
    int offset_;
    int count_;
};

#endif // DATA_SPAN_HPP_


// References:
// https://github.com/tdlib/td/blob/master/tdutils/td/utils/Slice-decl.h
