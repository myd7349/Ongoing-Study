#ifdef __linux
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/wait.h>

#include "../get_in_addr.h"
#include "../../../algorithm/algutils.h"
#include "../../../algorithm/string/strupr.c"


void sigchld_handler(int s)
{
    int saved_errno = errno;

    while (waitpid(-1, NULL, WNOHANG) > 0)
    {
    }

    errno = saved_errno;
}


int start_server(socket_t sockfd)
{
    struct sockaddr_storage client_addr;
    socklen_t sin_size;
    _TCHAR ipstr[INET6_ADDRSTRLEN];
    socket_t client_sockfd;
    pid_t fpid;

    _TCHAR message[1024];
    int length;

    struct sigaction sa;

    sa.sa_handler = sigchld_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;

    if (sigaction(SIGCHLD, &sa, NULL) == -1)
    {
        perror("sigaction");
        return EXIT_FAILURE;
    }

    printf("Server is waiting for connections...\n");

    while (1)
    {
        sin_size = sizeof client_addr;
        client_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &sin_size);
        if (client_sockfd == INVALID_SOCKET)
        {
            print_error_ex(_T("accpet"));
            continue;
        }

        if (inet_ntop(client_addr.ss_family,
            get_in_addr((struct sockaddr *)&client_addr),
            ipstr, sizeof(ipstr) / sizeof(ipstr[0])) != NULL)
        {
            _ftprintf(stdout, _T("Got connection from: %s.\n"), ipstr);
            fpid = fork();
            if (fpid < 0)
            {
                _ftprintf(stderr, _T("fork failed.\n"));
                break;
            }
            else if (fpid == 0)
            {
                // Child process doesn't need the listener
                closesock(sockfd);
                
                _stprintf(message, _T("Welcome! Worker [%u] is serving you!\n"), (unsigned)fpid);
                if (send(client_sockfd, (const char *)message, (_tcslen(message) + 1) * sizeof(_TCHAR), 0) == SOCKET_ERROR)
                {
                    print_error_ex(_T("send"));
                    closesock(client_sockfd);
                    exit(0);
                }

                while (1)
                {
                    length = recv(client_sockfd, (char *)message, sizeof(message), 0);
                    if (length == SOCKET_ERROR)
                    {
                        _ftprintf(stderr, _T("[%u] Failed to receive message from client <%s>: "), (unsigned)fpid, ipstr);
                        print_error_ex(_T("recv"));
                        exit(0);
                    }

                    length /= sizeof(_TCHAR);
                    length = MIN(length, ARRAYSIZE(message) - 1);
                    message[length] = _T('\0');

                    _tprintf(_T("[%u] Received message from client <%s>: %s\n"), (unsigned)fpid, ipstr, message);
                    _tcsupr(message);

                    if (send(client_sockfd, (const char *)message, (_tcslen(message) + 1) * sizeof(_TCHAR), 0) == -1)
                    {
                        _ftprintf(stderr, _T("[%u] Failed to send reply message to client <%s>: "), (unsigned)fpid, ipstr);
                        print_error_ex(_T("send"));
                    }
                }

                closesock(client_sockfd);
            }
            else
            {
                // Parent process doesn't need this
                closesock(client_sockfd);
            }
        }
        else
        {
            fprintf(stderr, "inet_ntop failed.\n");
        }
    }
}
#endif


// References:
// Beej's Guide to Network Programming Using Internet Sockets, Ch6.1
