// 2017-04-28T19:16+08:00
#ifndef FILE_DATA_SOURCE_BASE_HPP_
#define FILE_DATA_SOURCE_BASE_HPP_

#include <functional>

#include "FileUtility.h"
#include "IFileDataSource.h"
#include "../strutils.hpp"

template <typename T>
class FileDataSourceBase : public IFileDataSource
{
public:
    FileDataSourceBase(std::function<double(T)> fn = std::function<double(T)>())
        : trans_data_(fn), position_(0)
    {
    }

    virtual bool ReadFile(const std::wstring &fileName)
    {
        std::ifstream file(ws2s(fileName), std::ios::binary);
        if (!file.is_open())
            return false;

        unsigned fileSize = static_cast<unsigned>(GetFileSize(file));

        const int channelCount = GetChannelCount();

        assert(channelCount > 0);
        unsigned samplingCount = fileSize / (sizeof(T) * channelCount);

        std::vector<T> rawData(samplingCount * channelCount);
        T *buffer = rawData.data();
        file.read(reinterpret_cast<decltype(file)::char_type *>(buffer),
                  rawData.size() * sizeof(T) / sizeof(decltype(file)::char_type));

        data_.resize(channelCount);
        for (int c = 0; c < channelCount; ++c)
            data_[c].resize(samplingCount);

        std::function<double(T)> trans_data = GetDataTransFn();

        if (trans_data)
        {
            for (int c = 0; c < channelCount; ++c)
            {
                for (unsigned i = 0; i < samplingCount; ++i)
                {
                    data_[c][i] = trans_data(buffer[i * channelCount + c]);
                }
            }
        }
        else
        {
            for (int c = 0; c < GetChannelCount(); ++c)
            {
                for (unsigned i = 0; i < samplingCount; ++i)
                {
                    data_[c][i] = buffer[i * channelCount + c];
                }
            }
        }

        return true;
    }

    virtual int GetLength() const
    {
        return data_.empty() ? 0 : static_cast<int>(data_[0].size());
    }

    virtual int GetPosition() const
    {
        return position_;
    }

    virtual void SetPosition(int position)
    {
        bool isValidPosition = position >= 0 && position < GetLength();
        assert(isValidPosition);
        if (isValidPosition)
            position_ = position;
    }

    virtual DataSpan Read(int id, int offset, int count)
    {
        bool isValidId = id >= 0 && id < GetChannelCount();
        assert(isValidId);
        if (!isValidId)
            return DataSpan();

        bool isValidOffset = offset >= 0 && offset < GetLength();
        assert(isValidOffset);
        if (!isValidOffset)
            return DataSpan();

        assert(count >= 0);
        if (count <= 0)
            return DataSpan();

        count = std::min<int>(count, GetLength() - offset);
        return DataSpan(GetChannelData(id), offset, count);
    }

private:
    std::function<double(T)> GetDataTransFn() const
    {
        return trans_data_;
    }

    const std::vector<double> &GetChannelData(int channelNo) const
    {
        assert(channelNo >= 0 && channelNo < GetChannelCount());
        if (channelNo >= 0 && channelNo < GetChannelCount())
            return data_[channelNo];

        return dummy_;
    }

    std::vector<std::vector<double>> data_;
    std::vector<double> dummy_;
    std::function<double(T)> trans_data_;

    int position_;
};

template <>
std::function<double(short)> FileDataSourceBase<short>::GetDataTransFn() const
{
    std::function<double(short)> trans_data = [](short v) { return v / 1000.0; };
    return trans_data;
}

#endif // FILE_DATA_SOURCE_BASE_HPP_

// References:
// [Template specialization of a single method from a templated class](https://stackoverflow.com/questions/1723537/template-specialization-of-a-single-method-from-a-templated-class)
