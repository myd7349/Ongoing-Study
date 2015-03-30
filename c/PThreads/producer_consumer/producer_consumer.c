/* 2014-04-07T18:30+08:00 */
#include <stdio.h>

#include <pthread.h>

#define MAX (100000) /* how many numbers to produce */

pthread_mutex_t the_mutex;
pthread_cond_t cond_c;
pthread_cond_t cond_p;
int buffer = 0; /* buffer used between producer and consumer */

/* produce data */
void *producer(void *ptr)
{
    int i;

    for (i = 1; i <= MAX; ++i) {
        pthread_mutex_lock(&the_mutex); /* get exclusive access to buffer */

        while (buffer != 0) {
            pthread_cond_wait(&cond_p, &the_mutex);
        }

        buffer = i; /* put item in buffer */

        pthread_cond_signal(&cond_c); /* wake up consumer */
        pthread_mutex_unlock(&the_mutex); /* release access to buffer */
    }

    pthread_exit(NULL);
}

/* consume data */
void *consumer(void *ptr)
{
    int i;

    for (i = 1; i <= MAX; ++i) {
        pthread_mutex_lock(&the_mutex); /* get exclusive access to buffer */

        while (buffer == 0) {
            pthread_cond_wait(&cond_c, &the_mutex);
        }

        buffer = 0; /* tack item out of buffer */

        pthread_cond_signal(&cond_p); /* wake up producer */
        pthread_mutex_unlock(&the_mutex); /* release access to buffer */
    }

    pthread_exit(NULL);
}

int main(void)
{
    pthread_t pro_thread;
    pthread_t con_thread;

    pthread_mutex_init(&the_mutex, 0);
    pthread_cond_init(&cond_c, 0);
    pthread_cond_init(&cond_p, 0);

    pthread_create(&con_thread, 0, consumer, 0);
    pthread_create(&pro_thread, 0, producer, 0);

    pthread_join(pro_thread, 0);
    pthread_join(con_thread, 0);

    pthread_cond_destroy(&cond_c);
    pthread_cond_destroy(&cond_p);
    pthread_mutex_destroy(&the_mutex);

    return 0;
}
