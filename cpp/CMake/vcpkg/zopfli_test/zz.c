#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <zopfli.h>

#define BUFF_SIZE (1024 * 1024)


int main(int argc, char *argv[])
{
    FILE *in_fp = NULL;
    FILE *out_fp = NULL;

    unsigned char *in_buffer = NULL;

    size_t out_fn_len = 0;
    
    ZopfliOptions options;
    ZopfliFormat format = ZOPFLI_FORMAT_ZLIB;

    size_t src_bytes = 0;
    size_t dst_bytes = 0;

    if (argc != 3)
    {
        puts("Usage:\n    zz <infile> <outfile>");
        return 0;
    }

    in_fp = fopen(argv[1], "rb");
    if (in_fp == NULL)
    {
        fprintf(stderr, "Failed to open: %s: %s\n", argv[1], strerror(errno));
        return EXIT_FAILURE;
    }

    out_fn_len = strlen(argv[2]);
    if (out_fn_len > 3 && strcmp(argv[2] + out_fn_len - 3, ".gz") == 0)
        format = ZOPFLI_FORMAT_GZIP;

    out_fp = fopen(argv[2], "wb");
    if (out_fp == NULL)
    {
        fclose(in_fp);
        fprintf(stderr, "Failed to write: %s: %s\n", argv[2], strerror(errno));
        return EXIT_FAILURE;
    }

    in_buffer = malloc(BUFF_SIZE);
    if (in_buffer == NULL)
    {
        fclose(in_fp);
        fclose(out_fp);
        return EXIT_FAILURE;
    }

    ZopfliInitOptions(&options);

    while (1)
    {
        unsigned char *out_buffer = NULL;
        size_t out_size = 0;

        size_t res = fread(in_buffer, 1, BUFF_SIZE, in_fp);

        if (res == 0 || ferror(in_fp))
            break;

        src_bytes += res;

        ZopfliCompress(&options, format, in_buffer, res, &out_buffer, &out_size);

        res = fwrite(out_buffer, 1, out_size, out_fp);
        if (ferror(out_fp))
        {
            free(out_buffer);
            break;
        }

        free(out_buffer);

        dst_bytes += out_size;

        if (feof(in_fp))
            break;
    }

    fclose(in_fp);
    fclose(out_fp);

    free(in_buffer);

    printf("Before: %zu bytes\nAfter: %zu bytes\n", src_bytes, dst_bytes);

    return 0;
}
