#include "humanize.h"

#include <cmath>
#include <cstdio>


std::string GetReadableFileSize(std::int64_t bytes, bool si, unsigned digits)
{
    if (bytes < 0L)
        return "";

    char buffer[64] = "";

    int unit = si ? 1000 : 1024;
    if (bytes < unit)
        return std::to_string(bytes) + " B";

    int digit_group = static_cast<int>(std::log(bytes) / std::log(unit));
    std::string unit_prefix(1, "kMGTPEZY"[digit_group - 1]);
    if (!si)
        unit_prefix += 'i';

    std::string format = "%." + std::to_string(digits) + "f %sB";
    std::sprintf(buffer, format.c_str(), bytes / std::pow(unit, digit_group), unit_prefix.c_str());
    return buffer;
}


// References:
// https://stackoverflow.com/questions/3758606/how-to-convert-byte-size-into-human-readable-format-in-java
// https://stackoverflow.com/questions/3758606/how-to-convert-byte-size-into-human-readable-format-in-java
// https://www.zhihu.com/question/266520566/answer/361084338
// Ongoing-Study/cpp/Win32/MFC/Utility.h:GetReadableFileSize
// [convert astronomically large numbers into human readable form in C/C++](https://stackoverflow.com/questions/1499156/convert-astronomically-large-numbers-into-human-readable-form-in-c-c)
// [humanize_number.c](http://cvsweb.netbsd.org/bsdweb.cgi/src/lib/libc/gen/humanize_number.c?rev=1.14&content-type=text/x-cvsweb-markup&only_with_tag=MAIN)
// https://github.com/NetBSD/src/blob/trunk/lib/libc/gen/humanize_number.c
