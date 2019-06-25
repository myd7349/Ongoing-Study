#ifndef BASE64_H_
#define BASE64_H_

#include <stddef.h>


#ifdef __cplusplus
extern "C"
{
#endif

typedef enum
{
    B64F_NORMAL  = 0x11,
    B64F_URLSAFE = 0x12,
} B64_FLAGS;

size_t base64_encode_length(size_t len);

void *base64_encode(const void *data, size_t len, void *out_buffer, size_t *out_len, B64_FLAGS flags);

char *easy_base64_encode(const void *data, size_t len, char *out, size_t out_len);

#ifdef __cplusplus
}
#endif

#endif // BASE64_H_
