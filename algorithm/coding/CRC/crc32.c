#include "crc32.h"

#include <assert.h>
#include <stdio.h>

//#include "../../algutils.h"

// zipfile.py
/*
try:
    import zlib # We may need its compression method
    crc32 = zlib.crc32
except ImportError:
    zlib = None
    crc32 = binascii.crc32

...
    def _GenerateCRCTable():
        """Generate a CRC-32 table.

        ZIP encryption uses the CRC32 one-byte primitive for scrambling some
        internal keys. We noticed that a direct implementation is faster than
        relying on binascii.crc32().
        """
        poly = 0xedb88320
        table = [0] * 256
        for i in range(256):
            crc = i
            for j in range(8):
                if crc & 1:
                    crc = ((crc >> 1) & 0x7FFFFFFF) ^ poly
                else:
                    crc = ((crc >> 1) & 0x7FFFFFFF)
            table[i] = crc
        return table
    crctable = None

    def _crc32(self, ch, crc):
        """Compute the CRC32 primitive on one byte."""
        return ((crc >> 8) & 0xffffff) ^ self.crctable[(crc ^ ch) & 0xff]
*/


void crc32_init(crc32_t *crc32)
{
    assert(crc32 != NULL);

    crc32->type = CRC_32;
    crc32->check_value = 0xFFFFFFFF;
    crc32->feeding = true;
}


void crc32_feed(crc32_t *crc32, const void *data, size_t length)
{
    const char *buffer = data;
    size_t i;

    assert(crc32 != NULL && crc32->type == CRC_32 && crc32->feeding);
    assert(data != NULL || length == 0);

    for (i = 0; i < length; ++i)
    {
    }
}


crc32_checksum_t crc32_checksum(crc32_t *crc32)
{
    assert(crc32 != NULL && crc32->type == CRC_32);

    if (!crc32->feeding)
        return crc32->check_value;

    crc32->feeding = false;
    crc32->check_value ^= 0xFFFFFFFF;

    return crc32->check_value;
}


crc32_checksum_t crc32_easy_checksum(const void *data, size_t length)
{
    crc32_t crc32;

    crc32_init(&crc32);
    crc32_feed(&crc32, data, length);

    return crc32_checksum(&crc32);
}


char *crc32_checksum_hex(crc32_checksum_t crc32, char *buffer, size_t chars)
{
    assert(buffer != NULL && chars > CRC32_HEX_CHARS);
    snprintf(buffer, chars, "%08X", crc32);
    return buffer;
}


char *crc32_easy_checksum_hex(const void *data, size_t length, char *buffer, size_t chars)
{
    return crc32_checksum_hex(crc32_easy_checksum(data, length), buffer, chars);
}


// References:
// https://en.wikipedia.org/wiki/Cyclic_redundancy_check
// Computer Networks: A Top-Down Approach, 6th Edition, 5.2.3
// NSIS source code/crc32
// https://github.com/awslabs/aws-checksums/blob/master/include/aws/checksums/crc.h
