/* 2015-01-16T16:39+08:00 */

/* 
My environment: CentOS 6 x86_64 + GCC 4.4.7
Try:
1. gcc assign_thread_identity_v2.c -pthread -Wall 
2. g++ assign_thread_identity_v2.c -pthread -Wall
*/

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

#define NUM_OF_THRDS (10)

static void *routine(void *arg)
{
    intptr_t thrd_id = (intptr_t)arg;

    printf("Hello from thread #%d\n", (int)thrd_id);

    return NULL;
}

int main(void)
{
    pthread_t thrds[NUM_OF_THRDS];
    int i;
    int rc;
    void *res = NULL;

    for (i = 0; i < NUM_OF_THRDS; ++i) {
        rc = pthread_create(thrds + i, NULL, &routine, (void *)(intptr_t)i);
        assert(0 == rc);
        if (rc != 0) {
            fprintf(stderr, "Failed to create thread #%d.\n", i);
            exit(EXIT_FAILURE);
        }
    }

    for (i = 0; i < NUM_OF_THRDS; ++i) {
        rc = pthread_join(thrds[i], &res);
        assert(0 == rc);
        if (rc != 0) {
            fprintf(stderr, "Failed to join thread #%d.\n", i);
            exit(EXIT_FAILURE);        
        }
        free(res);
    }

    printf("Hello, world!");

    return 0;
}

/*
References:
[error: cast from 'void*' to 'int' loses precision](http://stackoverflow.com/questions/1640423/error-cast-from-void-to-int-loses-precision)
[Linux Pthread library, thread arguments](http://stackoverflow.com/questions/10871427/linux-pthread-library-thread-arguments)
[Why/when to use `intptr_t` for type-casting in C?](http://stackoverflow.com/questions/6326338/why-when-to-use-intptr-t-for-type-casting-in-c)
*/
