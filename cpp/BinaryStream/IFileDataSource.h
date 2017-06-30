// 2017-04-28T19:16+08:00
#ifndef INTERFACE_FILE_DATA_SOURCE_H_
#define INTERFACE_FILE_DATA_SOURCE_H_

#include <string>

#include "IDataSource.h"

class IFileDataSource : public IDataSource
{
public:
    virtual bool ReadFile(const std::wstring &fileName) = 0;
};

typedef std::shared_ptr<IFileDataSource> SharedFileDataSourcePtr;

#endif // INTERFACE_FILE_DATA_SOURCE_H_
