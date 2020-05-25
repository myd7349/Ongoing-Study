// 2018-01-26T15:56+08:00
#ifndef CRC_H_INCLUDED
#define CRC_H_INCLUDED

typedef enum
{
    CRC_32 = 32
} crc_type_t;

#define CRC_HEX_CHARS(crc_type) ((crc_type) / 4)
#define CRC32_HEX_CHARS CRC_HEX_CHARS(CRC_32)

#endif // CRC_H_INCLUDED
