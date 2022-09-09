#include <stddef.h>
#include <stdio.h>

int main(void)
{
    char s[] = { 'H', 'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l', 'd', '!' };
    unsigned len = sizeof(s);

    printf("%.*s\n", len, s);
    printf("[%*.*s]\n", 20, len, s);
    printf("[%-*.*s]\n", 20, len, s);

    fwrite(s, 1, len, stdout);
    putchar('\n');

    return 0;
}


// References:
// [How do I print a non-null-terminated string using printf?](https://stackoverflow.com/questions/2137779/how-do-i-print-a-non-null-terminated-string-using-printf)
// [Using printf with a non-null terminated string](https://stackoverflow.com/questions/3767284/using-printf-with-a-non-null-terminated-string)
