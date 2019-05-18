#include <locale.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../bzero.h"
#include "../tcpip.h"


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
    socket_t sockfd;
    struct sockaddr_in servaddr;
    char recvline[MAXLINE];
    int n;
    int res;
    uint16_t port;
    int count = 0;
    struct sockaddr_storage sockaddr;
    socklen_t name_len = sizeof(sockaddr);
    _TCHAR name_buff[INET_ADDRSTRLEN];

#ifdef _WIN32
    _tsetlocale(LC_ALL, _T(""));
#endif

    if (argc != 2 && argc != 3)
    {
        fprintf(stderr, "Usage:\n    a.out <IP> [port]\n");
        return EXIT_FAILURE;
    }

    if (argc == 3)
        port = (uint16_t)_ttoi(argv[2]);
    else
        port = 13; // daytime server

    TCP_IP_INIT();

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        print_error_ex(_T("socket"));
        return EXIT_FAILURE;
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);

    res = inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    if (res != 1)
    {
        if (res == 0)
            _ftprintf(stderr, _T("Invalid IPv4 address: %s\n"), argv[1]);
        else if (res == -1)
            print_error_ex(_T("inet_pton"));
        else
            fprintf(stderr, "Unexpected return value: %d.\n", res);

        return EXIT_FAILURE;
    }

    if (connect(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        print_error_ex(_T("connect"));
        closesock(sockfd);
        return EXIT_FAILURE;
    }

    // UNPv1 Exercise 4.2
    res = getsockname(sockfd, (struct sockaddr *)&sockaddr, &name_len);
    if (res == SOCKET_ERROR)
    {
        print_error_ex(_T("getsockname"));
        closesock(sockfd);
        return EXIT_FAILURE;
    }

    if (inet_ntop(sockaddr.ss_family, &((struct sockaddr_in *)&sockaddr)->sin_addr,
        name_buff, sizeof(name_buff) / sizeof(name_buff[0])) != NULL)
    {
        _ftprintf(stdout, _T("Socket name: %s:%hd\n"),
            name_buff,
            ((struct sockaddr_in *)&sockaddr)->sin_port);
    }
    else
    {
        fprintf(stderr, "inet_ntop failed.\n");
    }

#ifdef _WIN32
    while ((n = recv(sockfd, recvline, MAXLINE, 0)) > 0)
#else
    while ((n = read(sockfd, recvline, MAXLINE)) > 0)
#endif
    {
        count += 1; // UNPv1 Exercise 1.5

        recvline[n] = '\0';
        if (fputs(recvline, stdout) == EOF)
        {
            fprintf(stderr, "fputs failed(%d): %s\n", errno, strerror(errno));
            break;
        }
    }

    if (n < 0)
    {
#ifdef _WIN32
        print_error_ex(_T("recv"));
#else
        fprintf(stderr, "read failed(%d): %s\n", errno, strerror(errno));
#endif
    }

    // UNPv1 Exercise 1.5
    _tprintf(_T("count: %d\n"), count);

    closesock(sockfd);

    return 0;
}


// References:
// UNPv1, 3rd, Ch1.2
// https://stackoverflow.com/questions/10932473/how-do-i-use-the-wmain-entry-point-in-codeblocks
