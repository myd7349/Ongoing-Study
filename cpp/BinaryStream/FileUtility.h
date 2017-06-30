// 2016-07-05T19:00+08:00
#ifndef FILE_UTILITY_H_
#define FILE_UTILITY_H_

#include <fstream>
#include <string>

template <typename CharT>
inline long GetFileSize(std::basic_ifstream<CharT> &stream)
{
    if (!stream.is_open())
        return 0;

    auto prevPosition = stream.tellg();
    if (static_cast<long>(prevPosition) == -1)
        return 0;

    auto length = stream.seekg(0, stream.end).tellg();
    stream.seekg(prevPosition, stream.beg);

    if ((int)length != -1)
        return static_cast<long>(length);
    else
        return 0;
}

bool IsExists(const std::wstring &fileName);

#endif // FILE_UTILITY_H_
