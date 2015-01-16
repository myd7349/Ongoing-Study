/* 2015-01-16T16:39+08:00 */

/* gcc assign_thread_identity_v1.c -pthread -Wall */

#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

#define NUM_OF_THRDS (10)

static void *routine(void *arg)
{
    /* When I run this program on CentOS 6 x64, I got a warning here:
     * warning: cast from pointer to integer of different size
     */
    int thrd_id = (int)arg;

    printf("Hello from thread #%d\n", thrd_id);

    return NULL;
}

int main(void)
{
    pthread_t thrds[NUM_OF_THRDS];
    int i;
    int rc;

    for (i = 0; i < NUM_OF_THRDS; ++i) {
        /* When I run this program on CentOS 6 x64, I got a warning here:
         * warning: cast to pointer from integer of different size
         */
        rc = pthread_create(thrds + i, NULL, &routine, (void *)i);
        if (rc != 0) {
            fprintf(stderr, "Failed to create thread #%d.\n", i);
            exit(EXIT_FAILURE);
        }
    }

    printf("Hello, world!");

    return 0;
}
