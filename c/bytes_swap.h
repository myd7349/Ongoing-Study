#ifndef BYTES_SWAP_H_
#define BYTES_SWAP_H_

#include <stdint.h>


#if defined(_MSC_VER)
# include <stdlib.h>
# define BYTESWAP_U16(val) _byteswap_ushort((uint16_t)(val))
# define BYTESWAP_U32(val) _byteswap_ulong((uint32_t)(val))
# define BYTESWAP_U64(val) (uint64_t)_byteswap_uint64((uint64_t)(val))
#elif defined(__linux__)
# include <byteswap.h>
# define BYTESWAP_U16(val) bswap_16((val)) // __builtin_bswap16
# define BYTESWAP_U32(val) bswap_32((val)) // __builtin_bswap32
# define BYTESWAP_U64(val) bswap_64((val)) // __builtin_bswap64
#endif

#endif // BYTES_SWAP_H_


// References:
// https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/byteswap-uint64-byteswap-ulong-byteswap-ushort?view=vs-2019
// https://stackoverflow.com/questions/21527957/htonl-vs-builtin-bswap32
// https://github.com/edenhill/librdkafka/blob/master/src/snappy_compat.h
// http://man7.org/linux/man-pages/man3/bswap.3.html
// https://github.com/nemequ/portable-snippets/blob/master/builtin/builtin.h
// https://github.com/ciniml/WireGuard-ESP32-Arduino/blob/main/src/crypto.h
