#ifndef BASE64_H_
#define BASE64_H_

#include <stdbool.h>
#include <stddef.h>


#ifdef __cplusplus
extern "C"
{
#endif

typedef enum
{
    B64F_NORMAL     = 0x01,
    B64F_URLSAFE    = 0x02,
    B64F_NO_PADDING = 0x10,
} B64_FLAGS;


size_t base64_encoded_length(size_t len, B64_FLAGS flags);

void *base64_encode(const void *data, size_t len, void *out_buffer, size_t *out_len, B64_FLAGS flags);

size_t base64_decoded_length_unchecked(const void *base64, size_t len, B64_FLAGS flags);

size_t base64_decoded_length_slow(const void *base64, size_t len, B64_FLAGS flags);

bool base64_is_valid(const void *base64, size_t len, B64_FLAGS flags, size_t *decoded_len);

void *base64_decode(const void *base64, size_t len, void *data, size_t *out_len, B64_FLAGS flags);

char *easy_base64_encode(const void *data, size_t len, char *out, size_t out_len);

void *easy_base64_decode(const char *base64, void *data, size_t *out_len);

#ifdef __cplusplus
}
#endif

#endif // BASE64_H_
