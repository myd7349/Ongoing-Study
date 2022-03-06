#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[])
{
    size_t len = 0;
    int i;

    for (i = 0; i < argc; ++i)
        len += strlen(argv[i]);

    return (int)len;
}
