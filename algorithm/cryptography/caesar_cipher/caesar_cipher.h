// 2018-02-28T17:35+08:00
#ifndef CAESAR_CIPHER_H_INCLUDED
#define CAESAR_CIPHER_H_INCLUDED

#include <stddef.h>

typedef struct caesar_cipher_context_t *ccc_t;

ccc_t caesar_init(int shift);
void caesar_free(ccc_t *context);
char caesar_encode_char(ccc_t context, char ch);
char caesar_decode_char(ccc_t context, char ch);
int caesar_encode(ccc_t context, const char *plain_text, size_t len, char *cipher_text);
int caesar_decode(ccc_t context, const char *cipher_text, size_t len, char *plain_text);
const char *caesar_encode_cstr(ccc_t context, const char *plain_str, char *cipher_str, size_t len);
const char *caesar_decode_cstr(ccc_t context, const char *cipher_str, char *plain_text, size_t len);
const char *caesar_encode_cstr_simple(const char *plain_str, char *cipher_str, size_t len, int shift);
const char *caesar_decode_cstr_simple(const char *cipher_str, char *plain_text, size_t len, int shift);


#endif // CAESAR_CIPHER_H_INCLUDED
