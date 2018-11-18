#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "../../common.h"
#include "../get_in_addr.h"


#define MSG_MAX_LEN 1024


#if defined(WIN32)
void start_client(socket_t sockfd, const _TCHAR *ipstr)
{
    _TCHAR message[MSG_MAX_LEN + 1];
    int length;

    assert(sockfd != INVALID_SOCKET);
    assert(ipstr != NULL);

    while (true)
    {
        printf("me: ");
        _tscanf(_T("%") _T(STR(MSG_MAX_LEN)) _T("s"), message);

        if (send(sockfd, (const char *)message, (_tcslen(message) + 1) * sizeof(_TCHAR), 0) == -1)
        {
            _ftprintf(stderr, _T("Failed to send message to server: "));
            print_error_ex(_T("send"));
            break;
        }

        length = recv(sockfd, (char *)message, MSG_MAX_LEN * sizeof(_TCHAR), 0);
        if (length == SOCKET_ERROR)
        {
            _ftprintf(stderr, _T("Failed to receive message from server: "));
            print_error_ex(_T("recv"));
            break;
        }
        else
        {
            length /= sizeof(_TCHAR);
            message[length] = _T('\0');
            _putts(message);
        }
    }
}
#elif defined(__linux__)
void start_client(socket_t sockfd, const _TCHAR *ipstr)
{
    _TCHAR message[MSG_MAX_LEN + 1];
    int length;

    int maxfdp1;
    fd_set rset;

    assert(sockfd != INVALID_SOCKET);
    assert(ipstr != NULL);

    FD_ZERO(&rset);

    while (true)
    {
        FD_SET(fileno(stdin), &rset);
        FD_SET(sockfd, &rset);
        maxfdp1 = fileno(stdin) > sockfd ? fileno(stdin) + 1 : sockfd + 1;

        if (select(maxfdp1, &rset, NULL, NULL, NULL) > 0)
        {
            if (FD_ISSET(fileno(stdin), &rset))
            {
                printf("me: ");
                _tscanf(_T("%") _T(STR(MSG_MAX_LEN)) _T("s"), message);

                if (send(sockfd, (const char *)message, (_tcslen(message) + 1) * sizeof(_TCHAR), 0) == -1)
                {
                    _ftprintf(stderr, _T("Failed to send message to server: "));
                    print_error_ex(_T("send"));
                    break;
                }
            }

            if (FD_ISSET(sockfd, &rset))
            {
                length = recv(sockfd, (char *)message, MSG_MAX_LEN * sizeof(_TCHAR), 0);
                if (length == SOCKET_ERROR)
                {
                    _ftprintf(stderr, _T("Failed to receive message from server: "));
                    print_error_ex(_T("recv"));
                    break;
                }
                else
                {
                    length /= sizeof(_TCHAR);
                    message[length] = _T('\0');
                    _putts(message);
                }
            }
        }
        else
        {
            print_error_ex(_T("select"));
        }
    }
}
#else
# error Not tested yet!
#endif


// References:
// UNPv1, select/strcliselect01.c
