// 2017-12-30T20:43+08:00
#ifndef RFC1071_CHECKSUM_H_
#define RFC1071_CHECKSUM_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

uint16_t rfc1071_checksum(const void *data, size_t count);

#ifdef __cplusplus
}
#endif

#endif // RFC1071_CHECKSUM_H_
