// 2014-04-07T15:03+08:00
#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

#define NUMBER_OF_THREADS (10)

void *print_hello_world(void *tid)
{
    /* This function prints the thread's identifier and then exits. */
    printf("Hello, world. Greeting from thread %d.\n", (int)tid);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    /* The main program creates 10 threads and then exits. */
    pthread_t threads[NUMBER_OF_THREADS];
    int status;
    int i;

    for (i = 0; i < NUMBER_OF_THREADS; ++i) {
        printf("Main here. Creating thread %d...\n", i);
        status = pthread_create(&threads[i], NULL,
                                print_hello_world, (void *)i);
        if (status != 0) {
            printf("Oops. pthread_create returned error code %d.\n", status);
            return EXIT_FAILURE;
        }
    }

    for (i = 0; i < NUMBER_OF_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}

