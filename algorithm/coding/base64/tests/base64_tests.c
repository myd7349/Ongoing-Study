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


static void test(const char *data, size_t len, const char *expected, B64_FLAGS flags)
{
    char buffer[1024];
    size_t out_len = sizeof(buffer);

    if (len == 0)
        len = strlen(data);

    void *result = base64_encode(data, len, buffer, &out_len, flags);

    puts("------------------------------------------------------------");

    if (result == NULL)
    {
        fprintf(stderr, "Failed to encode data.\n");
    }
    else
    {
        fprintf(stdout, "Raw    (%zu): ", len);
        dump_data(data, len);

        fprintf(stdout, "Encoded(%zu): ", out_len);
        dump_data(result, out_len);
    }

    if (expected != NULL)
    {
        int ok = memcmp(result, expected, out_len) == 0;
        assert(ok);
        if (!ok)
            exit(EXIT_FAILURE);
    }

    char decoded[1024];
    size_t decoded_len = sizeof(decoded);
    base64_decode(result, out_len, decoded, &decoded_len, flags);
    fprintf(stdout, "Decoded(%zu): ", decoded_len);
    dump_data(decoded, decoded_len);

    assert(memcmp(data, decoded, decoded_len) == 0);
}


int main(void)
{
    unsigned char data[] =
    {
        0x04, 'B', '<', 0x96, 0xaa, 0x0e, 0xda, 'e',  0x94,
        'U',  '{', 0xd5, ']', 0xaa, 't',  0xb6, 0xd5, '_'
    };
    unsigned char data2[] = { 0x99, 0x00, '`', 0xd2, 'R', 0xae };
    unsigned char data3[] = { 0xce, '_', '{', 0xad };

    test("", 0, "", B64F_NORMAL);
    test("\0", 1, "AA==", B64F_NORMAL);
    test("\0", 1, "AA", B64F_NORMAL | B64F_NO_PADDING);
    test("\0\0", 2, "AAA=", B64F_NORMAL);
    test("\0\0", 2, "AAA", B64F_NORMAL | B64F_NO_PADDING);
    test("\0\0\0", 3, "AAAA", B64F_NORMAL);
    test("hello, world", 0, "aGVsbG8sIHdvcmxk", B64F_NORMAL);
    test("hello, world!", 0, "aGVsbG8sIHdvcmxkIQ==", B64F_NORMAL);
    test("hello, world!", 0, "aGVsbG8sIHdvcmxkIQ", B64F_NORMAL | B64F_NO_PADDING);
    test("hello, world!", 0, "aGVsbG8sIHdvcmxkIQ==", B64F_NORMAL | B64F_NO_PADDING);

    test((const char *)data, sizeof(data), "BEI8lqoO2mWUVXvVXap0ttVf", B64F_NORMAL);
    test((const char *)data2, sizeof(data2), "mQBg0lKu", B64F_NORMAL);
    test((const char *)data3, sizeof(data3), "zl97rQ==", B64F_NORMAL);

    return 0;
}
