#ifndef CLIENT7Z_H
#define CLIENT7Z_H

#include <string>


#include "C/7zTypes.h"
#include "Common/Common.h"
#include "Common/MyString.h"
#include "7zip/Archive/IArchive.h"


#define CLIENT7Z_LOG_ON (1)

#ifndef Client7zPrint
# if CLIENT7Z_LOG_ON
#  include <cstdio>
#  define Client7zPrint(str) std::fputs((str), stdout)
# else
#  define Client7zPrint(str) ((void)0)
# endif
#endif


class IArchiveExtractEventsSubscriber
{
public:
    virtual ~IArchiveExtractEventsSubscriber()
    {
    }

    virtual void SetTotal(UInt64 size) = 0;
    virtual void SetCompleted(UInt64 completeValue) = 0;
    virtual void SetFilePath(const wchar_t *fileName);
    virtual void SetResult(NArchive::NExtract::NOperationResult result) = 0;
};


class Client7z
{
public:
    Client7z();
    ~Client7z();

    int Extract(const std::wstring archiveFilePath, const std::wstring &outputPath,
        IArchiveExtractEventsSubscriber *extractEventsSubscriber = nullptr);

private:
    Client7z(const Client7z &);
    Client7z &operator=(const Client7z &);

    HMODULE library_;
    Func_CreateObject createObjectFunc_;
};


#endif // CLIENT7Z_H
