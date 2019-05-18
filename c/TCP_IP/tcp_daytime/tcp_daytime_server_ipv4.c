#include <locale.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../../bzero.h"
#include "../sendall.h"

#if defined(__MINGW32__) || defined(__MINGW64__)
# if USING_UNICODE
#  include "mingw-unicode.c"
# endif

# include "../inet_pton.h"
# define inet_pton inet_pton_c
#endif

#define MAXLINE (1024)


int _tmain(int argc, _TCHAR **argv)
{
    socket_t listenfd;
    socket_t connfd;
    struct sockaddr_in servaddr;
    char buff[MAXLINE];
    time_t ticks;
    int res;
    uint16_t port;
    size_t len;
    size_t i;

    (void)len;
    (void)i;

#ifdef _WIN32
    _tsetlocale(LC_ALL, _T(""));
#endif

    TCP_IP_INIT();

    if (argc != 1 && argc != 2)
    {
        _putts(_T("Usage:\n    a.out [port]"));
        return EXIT_FAILURE;
    }

    if (argc == 2)
        port = (uint16_t)_ttoi(argv[1]);
    else
        port = 13; // daytime server

    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        print_error_ex(_T("socket"));
        return EXIT_FAILURE;
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port); 

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
#if 0
        if (sendall(connfd, buff, strlen(buff)) == 0)
            print_error_ex(_T("send"));
#else
        // UNPv1 Exercise 1.5
        len = strlen(buff);

        for (i = 0; i < len; ++i)
        {
#ifdef __linux
            if (write(connfd, buff + i, 1) < 0)
            {
                print_error_ex(_T("write"));
                break;
            }
#else
            if (send(connfd, buff + i, 1, 0) == SOCKET_ERROR)
            {
                print_error_ex(_T("send"));
                break;
            }
#endif
        }
#endif

        closesock(connfd);
    }

    closesock(listenfd);

    return 0;
}


// References:
// UNPv1, 3rd, Ch1.5, Ch2.12
// https://stackoverflow.com/questions/10932473/how-do-i-use-the-wmain-entry-point-in-codeblocks
