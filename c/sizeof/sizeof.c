#include <stdio.h>


int main(void)
{
    printf("%s\n", __FILE__);
    printf("%zu\n", sizeof(__FILE__));

    return 0;
}


// References:
// https://github.com/edenhill/librdkafka/pull/2585
