#include <stdio.h>
#include <threads.h>


static once_flag flag = ONCE_FLAG_INIT;


void do_once(void)
{
    puts("Hello, world!");
}


int func(void *data)
{
    call_once(&flag, do_once);
}


int main(void)
{
    thrd_t t1;
    thrd_t t2;
    thrd_t t3;

    thrd_create(&t1, func, NULL);
    thrd_create(&t2, func, NULL);
    thrd_create(&t3, func, NULL);

    thrd_join(t1, NULL);
    thrd_join(t2, NULL);
    thrd_join(t3, NULL);

    return 0;
}


// References:
// cppreference
// https://stackoverflow.com/questions/52239644/mingw-w64-c11-threads-h-not-found
// https://stackoverflow.com/questions/8859394/c11-thread-h-in-gcc
