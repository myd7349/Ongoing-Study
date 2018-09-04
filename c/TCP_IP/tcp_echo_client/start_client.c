#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "../../common.h"
#include "../tcpip.h"


#define MSG_MAX_LEN 1024


void start_client(socket_t sockfd, const _TCHAR *ipstr)
{
    _TCHAR message[MSG_MAX_LEN] = _T("");
    int length;
    size_t message_length;

    assert(sockfd != INVALID_SOCKET);
    assert(ipstr != NULL);
    (void)ipstr;

    while (true)
    {
        _fgetts(message, MSG_MAX_LEN, stdin);
        message_length = _tcslen(message);

        if (message_length > 1 && message[message_length - 1] == _T('\n'))
        {
            message[message_length - 1] = _T('\0');
            message_length -= 1;
        }

        if (send(sockfd, (const char *)message, (message_length + 1) * sizeof(_TCHAR), 0) == -1)
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
            _tprintf(_T("%s\n"), message);
        }
    }
}


// References:
// https://en.wikipedia.org/wiki/Echo_Protocol
// https://github.com/nikhilm/uvbook/blob/master/code/tcp-echo-server/main.c
// https://github.com/mafintosh/echo-servers.c
// man nc
// https://stackoverflow.com/questions/8375860/how-to-make-an-echo-server-with-bash
// https://serverfault.com/questions/346481/echo-server-with-netcat-or-socat
