// 2014-04-27T18:12+08:00
#include <stdio.h>
#include <stdlib.h>

#include <process.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#define NUMBER_OF_THREADS (10)

unsigned int __stdcall print_hello_world(void *tid)
{
    printf("Hello, world. Greeting from thread %d.\n", (int)tid);
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    HANDLE hThreads[NUMBER_OF_THREADS] = { NULL };
    int i;
    int count = 0;

    for (i = 0; i < NUMBER_OF_THREADS; ++i) {
        printf("Main here. Creating thread %d...\n", i);
        hThreads[i] = (HANDLE)_beginthreadex(NULL, 0,
                                          print_hello_world, (void *)i,
                                          0, NULL);
        if (0 == hThreads[i]) {
            printf("Oops. Error occurs while creating thread %d.\n", i);
            break;
        }
        ++count;
    }

    WaitForMultipleObjects(count, hThreads, TRUE, INFINITE);
    for (i = 0; i < count; ++i) {
        CloseHandle(hThreads[i]);
    }

    return 0;
}
