#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../get_in_addr.h"
#include "../sendall.h"


int start_server(socket_t listener_sockfd)
{
    fd_set master;
    fd_set read_fds;
    int    fdmax;
    int    i;
    int    j;

    socket_t                 client_sockfd;
    socklen_t                addrlen;
    struct sockaddr_storage  client_addr;
    _TCHAR                   ipstr[INET6_ADDRSTRLEN];

    _TCHAR content[1024];
    int    nbytes;
    _TCHAR message[sizeof(content)/sizeof(content[0]) + 32];

    FD_ZERO(&master);
    FD_ZERO(&read_fds);

    // add the listener to the master set
    FD_SET(listener_sockfd, &master);
    fdmax = (int)listener_sockfd;

    while (true)
    {
        read_fds = master;
        if (select(fdmax + 1, &read_fds, NULL, NULL, NULL) == -1)
        {
            print_error_ex(_T("select"));
            return EXIT_FAILURE;
        }

        for (i = 0; i <= fdmax; ++i)
        {
            if (FD_ISSET(i, &read_fds))
            {
                if ((socket_t)i == listener_sockfd)
                {
                    // handle new connections
                    addrlen = sizeof(client_addr);
                    client_sockfd = accept(listener_sockfd, (struct sockaddr *)&client_addr, &addrlen);

                    if (client_sockfd == INVALID_SOCKET)
                    {
                        print_error_ex(_T("accept"));
                    }
                    else
                    {
                        FD_SET(client_sockfd, &master);

                        if (client_sockfd > (socket_t)fdmax)
                            fdmax = (int)client_sockfd;

                        if (inet_ntop(client_addr.ss_family,
                            get_in_addr((struct sockaddr *)&client_addr),
                            ipstr, sizeof(ipstr) / sizeof(ipstr[0])) != NULL)
                            _ftprintf(stdout, _T("Got connection from: %s.\n"), ipstr);
                        else
                            fprintf(stderr, "inet_ntop failed.\n");
                    }
                }
                else
                {
                    // handle data from a client
                    nbytes = recv((socket_t)i, (char *)content, sizeof(content), 0);

                    if (nbytes == SOCKET_ERROR)
                    {
                        _ftprintf(stderr, _T("Failed to receive data from client %d: "), i);
                        print_error_ex(_T("recv"));
                        FD_CLR(i, &master); // remove from master set
                    }
                    else if (nbytes == 0)
                    {
                        _ftprintf(stdout, _T("Connection with client %d is closed by the client.\n"), i);
                        closesock((socket_t)i);
                        FD_CLR(i, &master); // remove from master set
                    }
                    else
                    {
                        _stprintf(message, _T("%d: %s"), i, content);
                        _putts(message);

                        // send it to everyone in the room
                        for (j = 0; j <= fdmax; ++j)
                        {
                            if (FD_ISSET(j, &master) && (socket_t)j != listener_sockfd && j != i)
                            {
                                if (send((socket_t)j, (const char *)message, (_tcslen(message) + 1) * sizeof(_TCHAR), 0) == SOCKET_ERROR)
                                    print_error_ex(_T("send"));
                            }
                        }
                    }
                }
            }
        }
    }

    return 0;
}


// References:
// Beej's Guide to Network Programming, P35-P38
// https://github.com/beejjorgensen/bgnet/blob/master/examples/selectserver.c
