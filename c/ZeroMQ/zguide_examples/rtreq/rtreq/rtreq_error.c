// 2015-01-16T09:56+08:00
// ROUTER-to-REQ example

#include "../zhelpers.h"

#include <pthread.h>

#ifdef _MSC_VER
# pragma comment(lib, "pthreadVC2.lib")
#endif

#define NBR_WORKERS (10)

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

#define dprint printf

static void *worker_task(void *args)
{
    //int id = (int)args;
    pthread_mutex_lock(&mutex);
    int id = *(int *)(args);
    pthread_mutex_unlock(&mutex);

    void *context = zmq_ctx_new();
    dprint("%d zmq_ctx_new\n", id);
    assert(context != NULL);
    void *worker = zmq_socket(context, ZMQ_REQ);
    dprint("%d zmq_socket\n", id);
    assert(worker != NULL);
    s_set_id(worker); // Set a printable identity
    zmq_connect(worker, "tcp://localhost:5671");
    //zmq_connect(worker, "inproc://examples");
    //zmq_connect(worker, "ipc://routing.ipc");
    dprint("%d zmq_connect\n", id);
    int total = 0;
    while (1) {
        // Tell the broker we're ready for work
        s_send(worker, "Hi Boss");
        dprint("%d s_send\n", id);
        // Get workload from broker, until finished
        char *order = s_recv(worker);
        dprint("%d s_recv\n", id);
        int finished = (strcmp(order, "Fired!") == 0);
        free(order);
        if (finished) {
            printf("[%d] Completed: %d tasks\n", id, total);
            break;
        } 
        total++;

        // Do some random work
        int workload = randof(500) + 1;
        s_sleep(workload);
    }

    zmq_close(worker);
    zmq_ctx_destroy(context);

    return NULL;
}

// split main task
// While this example runs in a single process, that is only to make
// it easier to start and stop the example. Each thread has its own
// context and conceptually acts as a separate process.
int main(void)
{
    void *context = zmq_ctx_new();
    void *broker = zmq_socket(context, ZMQ_ROUTER);

    zmq_bind(broker, "tcp://*:5671");
    //zmq_bind(broker, "inproc://examples");
#if 0
    int res;
    res = zmq_bind(broker, "ipc://routing.ipc");
    assert(res == -1);
#endif

    srandom((unsigned int)time(NULL));

    int worker_nbr;
    for (worker_nbr = 0; worker_nbr < NBR_WORKERS; worker_nbr++) {
        pthread_t worker;
        pthread_mutex_lock(&mutex);
        int rc = pthread_create(&worker, NULL, worker_task, &worker_nbr);
        pthread_mutex_unlock(&mutex);
        //int rc = pthread_create(&worker, NULL, worker_task, (void *)worker_nbr);
        assert(0 == rc);
    }

    // Run for five seconds and then tell workers to end
    int64_t end_time = s_clock() + 5000;
    int workers_fired = 0;
    while (1) {
        // Next message gives us least recently used worker
        char *identity = s_recv(broker);
        s_sendmore(broker, identity);
        free(identity);
        free(s_recv(broker)); // Envelope delimiter
        free(s_recv(broker)); // Response from worker
        s_sendmore(broker, "");

        // Encourage workers until it's time to fire them
        if (s_clock() < end_time) {
            s_send(broker, "Work harder");
        } else {
            s_send(broker, "Fired!");
            if (++workers_fired == NBR_WORKERS) {
                break;
            }
        }
    }

    zmq_close(broker);
    zmq_ctx_destroy(context);

    PAUSE();

    return 0;
}
