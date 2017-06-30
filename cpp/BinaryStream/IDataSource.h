// 2017-04-28T19:16+08:00
#ifndef INTERFACE_DATA_SOURCE_H_
#define INTERFACE_DATA_SOURCE_H_

#include <memory>

#include "DataSpan.hpp"

class IDataSource
{
public:
    virtual ~IDataSource() {}
    virtual int GetChannelCount() const = 0;
    virtual int GetSamplingRate() const = 0;
    virtual int GetLength() const = 0;
    virtual int GetPosition() const = 0;
    virtual void SetPosition(int position) = 0;
    virtual DataSpan Read(int id, int offset, int count) = 0;
};

typedef std::shared_ptr<IDataSource> SharedDataSourcePtr;

#endif // INTERFACE_DATA_SOURCE_H_
