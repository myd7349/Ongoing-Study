#include <stdio.h>

#include "../../algutils.h"
#include "caesar_cipher.h"


int main()
{
    char plain[1024];
    char cipher[1024];

    const char *plain1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char *plain2 = "THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG";
    const char *plain3 = "Hello, world!";
    const char *plain4 = "exxegoexsrgi";
    const char *plain5 = "bob, i love you. alice";

    int i;

    printf("Cipher: %s.\n", caesar_encode_cstr_simple(plain1, ARRAY(cipher), 23));
    printf("Cipher: %s.\n", caesar_encode_cstr_simple(plain2, ARRAY(cipher), 23));
    printf("Plain: %s.\n", caesar_decode_cstr_simple(cipher, ARRAY(plain), 23));
    printf("Cipher: %s.\n", caesar_encode_cstr_simple(plain3, ARRAY(cipher), 23));
    printf("Plain: %s.\n", caesar_decode_cstr_simple(cipher, ARRAY(plain), 23));

    for (i = -27; i <= 27; ++i)
        printf("[%03d] %s.\n", i, caesar_decode_cstr_simple(plain4, ARRAY(plain), i));

    printf("Cipher: %s.\n", caesar_encode_cstr_simple(plain5, ARRAY(cipher), 3));
    printf("Plain: %s.\n", caesar_decode_cstr_simple(cipher, ARRAY(plain), 3));

    return 0;
}
