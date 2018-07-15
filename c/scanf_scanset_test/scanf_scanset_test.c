#include <stdbool.h>
#include <stdio.h>

#include "../common.h"
#include "../flushinp.h"


#define INPUT_MAX_LEN 12


int main()
{
    char msg[INPUT_MAX_LEN + 1];

    while (true)
    {
        int len;
        printf("Please input a string with no more than " STR(INPUT_MAX_LEN) " characters: ");
        if (scanf("%" STR(INPUT_MAX_LEN) "[^\n]%n", msg, &len) == 1)
            printf("Nice work! And your input is: <%s>(%d characters)\n", msg, len);

        flushinp();

        printf("Please input a hexadecimal number with no more than 10 chars: ");
        if (scanf("%10[A-Fa-f0-9]%n", msg, &len) == 1)
            printf("Nice work! And your input is: <%s>(%d characters)\n", msg, len);
        else
            printf("Are you kidding???\n");

        flushinp();
    }

    return 0;
}


// References:
// https://stackoverflow.com/questions/12784642/run-time-check-failure-2-stack-around-the-variable-was-corrupted
// http://www.cplusplus.com/reference/cstdio/scanf/
// https://zhidao.baidu.com/question/577533040.html
// https://blog.csdn.net/wesweeky/article/details/6439777
