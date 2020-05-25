#include <stdio.h>

#include "../../algutils.h"
#include "crc32.h"


int main()
{
    char crc32[CRC32_HEX_CHARS + 1];
    printf("CRC32: %s\n", crc32_easy_checksum_hex(NULL, 0, ARRAY(crc32)));

    return 0;
}
