#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include <process.h>

#include "../get_in_addr.h"


typedef struct
{
    socket_t sockfd;
    // Input
    _TCHAR in_buffer[4];
    OVERLAPPED ov_in;
    // Output
    int out_buffer_index;
    _TCHAR out_buffer[1024];
    OVERLAPPED ov_out;
    DWORD bytes_written;
} iocp_context_t;


void issue_read(iocp_context_t *ctx)
{
    int i = 0;
    BOOL ok;
    DWORD error;
    int bytes_read;

    assert(ctx != NULL);

    while (++i)
    {
        ok = ReadFile(
            (HANDLE)ctx->sockfd,
            ctx->in_buffer,
            sizeof(_TCHAR),
            &bytes_read,
            &ctx->ov_in
        );

        if (ok)
            return;

        error = GetLastError();

        if (error == ERROR_IO_PENDING)
            return;

        if (error == ERROR_INVALID_USER_BUFFER ||
            error == ERROR_NOT_ENOUGH_QUOTA ||
            error == ERROR_NOT_ENOUGH_MEMORY)
        {
            if (i == 5)
            {
                Sleep(50);
                continue;
            }

            fprintf(stderr, "issue_read - System ran out of non-paged space.\n");
        }

        break;
    }

    fprintf(stderr, "issue_read - ReadFile failed.\n");
}


unsigned __stdcall worker_routine(void *arg)
{
    BOOL result;
    DWORD bytes_read;
    iocp_context_t *ctx;
    LPOVERLAPPED pov;
    HANDLE iocp_handle = arg;
    DWORD thread_id = GetCurrentThreadId();

    assert(iocp_handle != NULL);

    while (true)
    {
        result = GetQueuedCompletionStatus(
            iocp_handle,
            &bytes_read,
            &(DWORD)ctx,
            &pov,
            INFINITE
        );

        if (!result && pov == NULL)
        {
            _ftprintf(stderr, _T("[%lu] Illegal call to GetQueuedCompletionStatus.\n"), thread_id);
            return EXIT_FAILURE;
        }
        else if (!result && pov != NULL)
        {
            closesock(ctx->sockfd);
            free(ctx);
            _ftprintf(stderr, _T("[%lu] I/O operation failed.\n"), thread_id);
        }
        else if (bytes_read == 0)
        {
            closesock(ctx->sockfd);
            free(ctx);
            _ftprintf(stderr, _T("[%lu] I/O - End of file.\n"), thread_id);
        }
        else
        {
            _TCHAR *pch = ctx->out_buffer + ctx->out_buffer_index++;
            *pch++ = ctx->in_buffer[0];
            *pch = _T('\0');

            if (ctx->in_buffer[0] == _T('\n') || ctx->in_buffer[0] == _T('\0'))
            {
                _tprintf(_T("[%lu] Received message from client: %s\n"), thread_id, ctx->out_buffer);
                _tcsupr(ctx->out_buffer);
                WriteFile(
                    (HANDLE)ctx->sockfd,
                    ctx->out_buffer,
                    (ctx->out_buffer_index + 1) * sizeof(_TCHAR),
                    &ctx->bytes_written,
                    &ctx->ov_out
                );

                ctx->out_buffer_index = 0;
            }

            issue_read(ctx);
        }
    }

    return 0;
}


void create_worker_threads(HANDLE iocp_handle)
{
    SYSTEM_INFO si;
    DWORD thread_count;
    DWORD i;

    HANDLE thread;
    unsigned int thread_id;

    GetSystemInfo(&si);
    thread_count = si.dwNumberOfProcessors * 2 + 2;

    for (i = 0; i < thread_count; ++i)
    {
        thread = (HANDLE)_beginthreadex(
            NULL,
            0,
            (_beginthreadex_proc_type)worker_routine,
            iocp_handle,
            0,
            &thread_id);
        CloseHandle(thread);
        printf("Created working thread [%lu]: %u.\n", i, thread_id);
    }
}


int start_server(socket_t sockfd)
{
    struct sockaddr_storage client_addr;
    socklen_t sin_size;
    _TCHAR ipstr[INET6_ADDRSTRLEN];
    socket_t client_sockfd;
    const _TCHAR *welcome = _T("Welcome to the machine!");

    HANDLE iocp_handle = CreateIoCompletionPort(
        INVALID_HANDLE_VALUE,
        NULL,
        0,
        0
    );

    if (iocp_handle == NULL)
    {
        fprintf(stderr, "Failed to create IO completion port.\n");
        return EXIT_FAILURE;
    }

    create_worker_threads(iocp_handle);

    while (true)
    {
        sin_size = sizeof client_addr;
        client_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &sin_size);
        if (client_sockfd == INVALID_SOCKET)
        {
            print_error_ex(_T("accept"));
            continue;
        }

        if (inet_ntop(client_addr.ss_family,
            get_in_addr((struct sockaddr *)&client_addr),
            ipstr, sizeof(ipstr) / sizeof(ipstr[0])) != NULL)
        {
            iocp_context_t *ctx = NULL;

            _ftprintf(stdout, _T("Got connection from: %s.\n"), ipstr);

            if (send(client_sockfd, (const char *)welcome, (_tcslen(welcome) + 1) * sizeof(_TCHAR), 0) == SOCKET_ERROR)
            {
                _ftprintf(stderr, _T("Failed to send welcome message to client <%s>: "), ipstr);
                print_error_ex(_T("send"));
            }

            ctx = calloc(1, sizeof(iocp_context_t));
            if (ctx == NULL)
            {
                fprintf(stderr, "Failed to allocate memory for IOCP context.\n");
                return EXIT_FAILURE;
            }

            ctx->sockfd = client_sockfd;
            ctx->ov_out.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
            ctx->ov_out.hEvent = (HANDLE)((DWORD)ctx->ov_out.hEvent | 0x1);

            CreateIoCompletionPort(
                (HANDLE)client_sockfd,
                iocp_handle,
                (DWORD)ctx,
                0
            );

            issue_read(ctx);
        }
        else
        {
            fprintf(stderr, "inet_ntop failed.\n");
        }
    }

    return 0;
}


// References:
// Multithreading Applications in Win32, Chapter 06
// https://stackoverflow.com/questions/150355/programmatically-find-the-number-of-cores-on-a-machine
