#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sodium.h>

#include "../../../algorithm/coding/base64/tests/dump.c"


void hash_message(const char *message)
{
    puts("------------------------------------------------------------");

    unsigned char hash[crypto_generichash_BYTES];

    crypto_generichash(hash, sizeof hash, message, strlen(message), NULL, 0);

    printf("Raw message: %s\nHash: ", message);
    dump_data(hash, sizeof hash);
}


void hash_message_with_a_key(const char *message, const unsigned char *key, size_t key_size, int one_run)
{
    puts("------------------------------------------------------------");

    unsigned char hash[crypto_generichash_BYTES];

    if (one_run)
    {
        crypto_generichash(hash, sizeof hash, message, strlen(message), key, key_size);
    }
    else
    {
        crypto_generichash_state state;
        crypto_generichash_init(&state, key, key_size, sizeof hash);
        crypto_generichash_update(&state, message, strlen(message));
        crypto_generichash_final(&state, hash, sizeof hash);
    }

    printf("Raw message: %s\n", message);
    printf("Key: ");
    dump_data(key, key_size);
    printf("Hash: ");
    dump_data(hash, sizeof hash);
}


int main(void)
{
    int res = sodium_init();
    if (res < 0)
    {
        fprintf(stderr, "sodium_init failed: %d\n", res);
        return EXIT_FAILURE;
    }

    hash_message("Hello, world!");
    hash_message("Hello, world!");
    hash_message("Hello, world");

    unsigned char key[crypto_generichash_KEYBYTES];
    randombytes_buf(key, sizeof key);

    hash_message_with_a_key("Hello, world!", key, sizeof key, 1);
    hash_message_with_a_key("Hello, world!", key, sizeof key, 0);
    hash_message_with_a_key("Hello, world", key, sizeof key, 1);

    return 0;
}
