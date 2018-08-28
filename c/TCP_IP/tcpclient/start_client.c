#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "../../common.h"
#include "../get_in_addr.h"


#define MSG_MAX_LEN 1024


void start_client(socket_t sockfd, const _TCHAR *ipstr)
{
    _TCHAR message[MSG_MAX_LEN + 1];
    int length;

    assert(sockfd != INVALID_SOCKET);
    assert(ipstr != NULL);

    length = recv(sockfd, (char *)message, MSG_MAX_LEN * sizeof(_TCHAR), 0);
    if (length == SOCKET_ERROR)
        return;

    length /= sizeof(_TCHAR);
    message[length] = _T('\0');

    _tprintf(_T("Received message from server <%s>: %s\n"), ipstr, message);

    while (true)
    {
        printf("> ");
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
            _tprintf(_T("Received message from server <%s>: %s\n"), ipstr, message);
        }
    }
}
