#include <nanomsg/nn.h>
#include <nanomsg/reqrep.h>

#include "../nnhelper.hpp"


int main()
{
    int socket;
    int result;

    if ((socket = nn_socket(AF_SP, NN_REP)) < 0)
        nnh_fatal_error("nn_socket");

    if ((result = nn_bind(socket, "tcp://*:5678")) < 0)
        nnh_fatal_error("nn_bind");

    while (1)
    {
        std::string str = nnh_recv_string(socket);
        std::printf("Received \"%s\" ...\n", str.c_str());

        str = "Reply for \"" + str + "\"";
        nnh_sendstr(socket, str.c_str());
    }

    return nn_close(socket);
}
