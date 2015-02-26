/* 2015-01-16T16:39+08:00 */

/* 
My environment: CentOS 6 x86_64 + GCC 4.4.7
Try:
1. gcc assign_thread_identity_v1.c -pthread -Wall 
   There will be two warnings.
2. g++ assign_thread_identity_v1.c -pthread -Wall 
   There will be an compile-time error:
       assign_thread_identity_v1.c: In function ‘void* routine(void*)’:
       assign_thread_identity_v1.c:23: error: cast from ‘void*’ to ‘int’ loses precision
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

#define NUM_OF_THRDS (10)

static void *routine(void *arg)
{
    /* On CentOS 6 x86_64 with GCC 4.4.7: 
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
    void *res = NULL;

    for (i = 0; i < NUM_OF_THRDS; ++i) {
        /* On CentOS 6 x86_64 with GCC 4.4.7:
         * warning: cast to pointer from integer of different size
         */
        rc = pthread_create(thrds + i, NULL, &routine, (void *)i);
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
[is it necessary to call pthread_join()](http://stackoverflow.com/questions/10600250/is-it-necessary-to-call-pthread-join)
[Linux Pthread library, thread arguments](http://stackoverflow.com/questions/10871427/linux-pthread-library-thread-arguments)
*/
