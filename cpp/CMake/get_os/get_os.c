#include <stdio.h>

extern const char *get_os();

int main()
{
    printf("OS: %s\n", get_os());
    return 0;
}