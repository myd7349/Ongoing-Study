#include <stdio.h>

#define max_old(a, b) ((a) > (b) ? (a) : (b))

#define max(a, b) \
    ({ \
        typeof(a) a_ = (a); \
        typeof(b) b_ = (b); \
        a_ > b_ ? a_ : b_; \
    })


int main(void)
{
    int i, j;

    printf("%d\n", max(30, 20 + 11));

    i = j = 5;
    printf("%d\n", max_old(--i, ++j));
    printf("i: %d, j: %d\n", i, j);

    i = j = 5;
    printf("%d\n", max(--i, ++j));
    printf("i: %d, j: %d\n", i, j);

    return 0;
}


// References:
// https://github.com/microsoft/vcpkg/pull/5921
// https://github.com/edenhill/librdkafka/blob/v1.0.0/src/snappy_compat.h#L47-L50
// https://github.com/andikleen/snappy-c/blob/master/compat.h#L42-L45
// https://github.com/google/snappy/blob/1.1.7/snappy-stubs-internal.h#L194-L198
// https://stackoverflow.com/questions/7117427/c-block-becomes-expression-int-a-1-int-b-2-ab-equals-3
