#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../base64.h"


static void dump_data(const char *data, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        if (isprint((unsigned char)data[i]))
            printf("%c", data[i]);
        else
            printf("\\x%02x", (unsigned char)data[i]);
    }

    printf("\n");
}


static void test_encoding(const char *data, size_t len, const char *expected)
{
    char buffer[1024];
    if (len == 0)
        len = strlen(data);
    char *result = easy_base64_encode(data, len, buffer, sizeof(buffer));

    puts("------------------------------------------------------------");

    if (result == NULL)
    {
        fprintf(stderr, "Failed to encode data.\n");
    }
    else
    {
        fprintf(stdout, "Raw(%zu): ", len);
        dump_data(data, len);

        fprintf(stdout, "Encoded(%zu): ", strlen(result));
        dump_data(result, strlen(result));
    }

    if (expected != NULL)
    {
        int ok = strcmp(result, expected) == 0;
        assert(ok);
        if (!ok)
            exit(EXIT_FAILURE);
    }
}


int main(void)
{
    unsigned char data[] =
    {
        0x04, 'B', '<', 0x96, 0xaa, 0x0e, 0xda, 'e',  0x94,
        'U',  '{', 0xd5, ']', 0xaa, 't',  0xb6, 0xd5, '_'
    };

    test_encoding("", 0, "");
    test_encoding("\0", 1, "AA==");
    test_encoding("\0\0", 2, "AAA=");
    test_encoding("\0\0\0", 3, "AAAA");
    test_encoding("hello, world", 0, "aGVsbG8sIHdvcmxk");
    test_encoding("hello, world!", 0, "aGVsbG8sIHdvcmxkIQ==");

    test_encoding((const char *)data, sizeof(data), "BEI8lqoO2mWUVXvVXap0ttVf");

    return 0;
}
