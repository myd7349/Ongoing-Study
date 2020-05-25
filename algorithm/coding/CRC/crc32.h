#ifndef CRC32_H_INCLUDED
#define CRC32_H_INCLUDED

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "crc.h"


typedef uint32_t crc32_checksum_t;

typedef struct
{
    crc_type_t type;
    crc32_checksum_t check_value;
    bool feeding;
} crc32_t;

void crc32_init(crc32_t *crc32);
void crc32_feed(crc32_t *crc32, const void *data, size_t length);
crc32_checksum_t crc32_checksum(crc32_t *crc32);
crc32_checksum_t crc32_easy_checksum(const void *data, size_t length);
char *crc32_checksum_hex(crc32_checksum_t crc32, char *buffer, size_t chars);
char *crc32_easy_checksum_hex(const void *data, size_t length, char *buffer, size_t chars);

#endif // CRC32_H_INCLUDED
