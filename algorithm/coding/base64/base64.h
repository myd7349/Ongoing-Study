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

#ifdef __cplusplus

// C++ API
#include <string>
#include <vector>


inline std::string base64_encode(const void *data, size_t len, B64_FLAGS flags = B64F_NORMAL)
{
    size_t out_len = base64_encoded_length(len, flags);
    std::vector<char> base64(out_len);
    if (base64_encode(data, len, static_cast<void *>(base64.data()), &out_len, flags) != NULL)
        return std::string(base64.data(), out_len);
    else
        return "";
}


inline std::vector<unsigned char> base64_decode(const std::string &base64, B64_FLAGS flags = B64F_NORMAL)
{
    size_t out_len = base64_decoded_length_unchecked(base64.c_str(), base64.length(), flags);
    std::vector<unsigned char> data(out_len);
    
    if (base64_decode(base64.c_str(), base64.length(), data.data(), &out_len, flags) != NULL)
        data.resize(out_len);
    else
        data.clear();

    return data;
}

#endif

#endif // BASE64_H_
