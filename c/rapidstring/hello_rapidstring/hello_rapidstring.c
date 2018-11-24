#include <stdio.h>

#include <rapidstring.h>

int main()
{
    rapidstring s;

    rs_init_w(&s, "Hello, world!");

    puts(rs_data(&s));
    printf("%zu\n", rs_len(&s));

    return 0;
}