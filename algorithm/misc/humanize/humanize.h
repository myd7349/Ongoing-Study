// 2018-07-12T18:03+08:00
#ifndef HUMANIZE_H_INCLUDED
#define HUMANIZE_H_INCLUDED

#include <cstdint>
#include <string>


std::string GetReadableFileSize(std::int64_t bytes, bool si = false, unsigned digits = 2);


#endif // HUMANIZE_H_INCLUDED

