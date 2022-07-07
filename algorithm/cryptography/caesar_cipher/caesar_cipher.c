#include "caesar_cipher.h"

#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "../../algutils.h"


struct caesar_cipher_context_t
{
    char encoding_map[128];
    char decoding_map[128];
    int shift;
};


ccc_t caesar_init(int shift)
{
    ccc_t context = NULL;
    int ch;

    context = malloc(sizeof(struct caesar_cipher_context_t));
    if (context == NULL)
        return NULL;

    context->shift = shift;

    if (shift >= 26 || shift <= -26)
        shift = div(shift, 26).rem;

    if (shift < 0)
        shift += 26;

    for (ch = 'A'; ch <= 'Z'; ++ch)
    {
        char encoded_ch = (char)('A' + (((ch - 'A') + shift) % 26));
        context->encoding_map[ch] = encoded_ch;
        context->decoding_map[(int)encoded_ch] = ch;
    }


    for (ch = 'a'; ch <= 'z'; ++ch)
    {
        context->encoding_map[ch] = (char)(context->encoding_map[ch - 'a' + 'A'] + 'a' - 'A');
        context->decoding_map[ch] = (char)(context->decoding_map[ch - 'a' + 'A'] + 'a' - 'A');
    }

    return context;
}


void caesar_free(ccc_t *context)
{
    assert(context != NULL);

    if (*context != NULL)
    {
        free(*context);
        *context = NULL;
    }
}


char caesar_encode_char(ccc_t context, char ch)
{
    assert(context != NULL);
    return isalpha(ch) ? context->encoding_map[(int)ch] : ch;
}


char caesar_decode_char(ccc_t context, char ch)
{
    assert(context != NULL);
    return isalpha(ch) ? context->decoding_map[(int)ch] : ch;
}


int caesar_encode(ccc_t context, const char *plain_text, size_t len, char *cipher_text)
{
    size_t i;

    assert(context != NULL);
    assert(plain_text != NULL && len > 0 && cipher_text != NULL);

    for (i = 0; i < len; ++i)
        cipher_text[i] = caesar_encode_char(context, plain_text[i]);

    return 0;
}


int caesar_decode(ccc_t context, const char *cipher_text, size_t len, char *plain_text)
{
    size_t i;

    assert(context != NULL);
    assert(cipher_text != NULL && len > 0 && plain_text != NULL);

    for (i = 0; i < len; ++i)
        plain_text[i] = caesar_decode_char(context, cipher_text[i]);

    return 0;
}


const char *caesar_encode_cstr(ccc_t context, const char *plain_str, char *cipher_str, size_t len)
{
    size_t str_len;

    str_len = strlen(plain_str);
    if (str_len == 0 || len == 0)
        return NULL;

    len = MIN(str_len + 1, len);

    if (caesar_encode(context, plain_str, len - 1, cipher_str) != 0)
        return NULL;

    cipher_str[str_len] = '\0';

    return cipher_str;
}


const char *caesar_decode_cstr(ccc_t context, const char *cipher_str, char *plain_str, size_t len)
{
    size_t str_len;

    str_len = strlen(cipher_str);
    if (str_len == 0 || len == 0)
        return NULL;

    len = MIN(str_len + 1, len);

    if (caesar_decode(context, cipher_str, len - 1, plain_str) != 0)
        return NULL;

    plain_str[str_len] = '\0';

    return plain_str;
}


const char *caesar_encode_cstr_simple(const char *plain_str, char *cipher_str, size_t len, int shift)
{
    ccc_t context = caesar_init(shift);
    if (context == NULL)
        return NULL;

    caesar_encode_cstr(context, plain_str, cipher_str, len);

    caesar_free(&context);

    return cipher_str;
}


const char *caesar_decode_cstr_simple(const char *cipher_str, char *plain_str, size_t len, int shift)
{
    ccc_t context = caesar_init(shift);
    if (context == NULL)
        return NULL;

    caesar_decode_cstr(context, cipher_str, plain_str, len);

    caesar_free(&context);

    return plain_str;
}


// References:
// https://en.wikipedia.org/wiki/Caesar_cipher
// Computer Networking: A Top-Down Approach, 6th Edition, Chapter 8
// [C++ Caesar Cipher (ASCII Codes) | Algo for Beginners](https://www.youtube.com/watch?v=0ZxqLybllNQ)
