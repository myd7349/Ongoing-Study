#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

int main()
{
    union
    {
        uint8_t c[sizeof(uint16_t)];
        uint16_t s;
    } un;

    char buffer[sizeof(un.s)];

    un.s = 0x0201;

    if (un.c[0] == 1 && un.c[1] == 2)
        puts("Little Endian");
    else if (un.c[0] == 2 && un.c[1] == 1)
        puts("Big Endian");
    else
        puts("Unknown endianess!");

    FILE *fp = fopen("data.bin", "w+b");
    if (fp != NULL)
    {
        fwrite(&un.s, sizeof(un.s), 1, fp);

        rewind(fp);

        fread(buffer, 1, sizeof(buffer), fp);

        printf("0x%"PRIx8" 0x%"PRIx8"\n", buffer[0], buffer[1]);
        
        fclose(fp);
    }

    return 0;
}

// References:
// UNPv1, Chapter 3
// https://github.com/caryll/otfcc/blob/ad01e3608293a548bedf87704f35e4c0529804d3/lib/support/bin-io.h#L16-L23
// Ongoing-study/python/int_to_bytes.py
