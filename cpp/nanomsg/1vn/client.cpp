#include <nanomsg/nn.h>
#include <nanomsg/reqrep.h>

#include "../nnhelper.hpp"


int main(int argc, char *argv[])
{
    int socket;
    int result;

    if ((socket = nn_socket(AF_SP, NN_REQ)) < 0)
        nnh_fatal_error("nn_socket");

    if ((result = nn_connect(socket, "tcp://localhost:5678")) < 0)
        nnh_fatal_error("nn_connect");

    for (int i = 0; i < argc; ++i)
    {
        nnh_sendstr(socket, argv[i]);

        nnh_sleep(5000);

        std::string reply = nnh_recv_string(socket);
        std::printf("\"%s\"\n", reply.c_str());
    }

    return nn_close(socket);
}
