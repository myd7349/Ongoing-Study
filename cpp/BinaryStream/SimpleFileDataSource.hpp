// 2017-06-30T10:17+08:00
#ifndef SIMPLE_FILE_DATA_SOURCE_HPP_
#define SIMPLE_FILE_DATA_SOURCE_HPP_

#include "FileDataSourceBase.hpp"

template <typename T>
class SimpleFileDataSource : public FileDataSourceBase<T>
{
public:
    SimpleFileDataSource(int channelCount, int samplingRate)
        : channelCount_(channelCount), samplingRate_(samplingRate)
    {
        assert(channelCount > 0);
        assert(samplingRate > 0);
    }

    virtual int GetChannelCount() const
    {
        return channelCount_;
    }

    virtual int GetSamplingRate() const
    {
        return samplingRate_;
    }

private:
    int channelCount_;
    int samplingRate_;
};

#endif // SIMPLE_FILE_DATA_SOURCE_HPP_
