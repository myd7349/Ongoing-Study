#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../../bzero.h"
#include "../sendall.h"

#define MAXLINE (1024)


int _tmain()
{
    socket_t listenfd;
    socket_t connfd;
    struct sockaddr_in servaddr;
    char buff[MAXLINE];
    time_t ticks;
    int res;

#ifdef _WIN32
    _tsetlocale(LC_ALL, _T(""));
#endif

    TCP_IP_INIT();

    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        print_error_ex(_T("socket"));
        return EXIT_FAILURE;
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(13); // daytime server

    if ((res = bind(listenfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0)
    {
#if 0
        // On Win10, this will not translate error message correctly.
        closesock(listenfd);
        print_error_ex(_T("bind"));
#else
        print_error_ex(_T("bind"));
        closesock(listenfd);
#endif
        return EXIT_FAILURE;
    }

    if ((res = listen(listenfd, SOMAXCONN)) != 0)
    {
        print_error_ex(_T("listen"));
        closesock(listenfd);
        return EXIT_FAILURE;
    }

    while (1)
    {
        if ((connfd = accept(listenfd, (struct sockaddr *)NULL, NULL)) == INVALID_SOCKET)
        {
            print_error_ex(_T("accept"));
            break;
        }

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        if (sendall(connfd, buff, strlen(buff)) == 0)
            print_error_ex(_T("send"));

        closesock(connfd);
    }

    closesock(listenfd);

    return 0;
}


// References:
// UNPv1, 3rd, Ch1.5, Ch2.12
