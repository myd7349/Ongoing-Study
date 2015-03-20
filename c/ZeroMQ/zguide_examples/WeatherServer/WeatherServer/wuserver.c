// 2014-12-23T09:25+08:00

#include "../zhelpers.h"

int main(void)
{
    void *context = zmq_ctx_new();
    void *publisher = zmq_socket(context, ZMQ_PUB);
    int rc = zmq_bind(publisher, "tcp://*:5556");
    assert(rc == 0);
    srand((unsigned)time(NULL));
    while (1) {
        int zipcode, temperature, relhumidity;
        zipcode = 10001;// randof(100000);
        temperature = randof(215) - 80;
        relhumidity = randof(50) + 10;

        // Send message to all subscribers
        char update[20];
        sprintf(update, "%05d %d %d", zipcode, temperature, relhumidity);
        s_send(publisher, update);
        printf("%s\n", update);
    }

    zmq_close(publisher);
    zmq_ctx_destroy(context);
    return 0;
}