#ifdef _WIN32
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include <process.h>

#include "../get_in_addr.h"
#include "../../../algorithm/containers/dynamic_array.h"


typedef struct
{
    HANDLE handle;
    socket_t sockfd;
    LONG running;
    _TCHAR ipstr[INET6_ADDRSTRLEN];
} worker_context_t;


static unsigned int __stdcall worker_routine(worker_context_t *ctx)
{
    _TCHAR message[1024];
    int length;
    unsigned id = (unsigned)GetCurrentThreadId();

    assert(ctx != NULL);

    _stprintf(message, _T("Welcome! Worker [%u] is serving you!\n"), id);

    if (send(ctx->sockfd, (const char *)message, (_tcslen(message) + 1) * sizeof(_TCHAR), 0) != SOCKET_ERROR)
    {
        while (ctx->running)
        {
            length = recv(ctx->sockfd, (char *)message, sizeof(message), 0);
            if (length == SOCKET_ERROR)
            {
                _ftprintf(stderr, _T("[%u] Failed to receive message from client <%s>: "), id, ctx->ipstr);
                print_error_ex(_T("recv"));
                break;
            }

            length /= sizeof(_TCHAR);
            length = MIN(length, ARRAYSIZE(message) - 1);
            message[length] = _T('\0');

            _tprintf(_T("[%u] Received message from client <%s>: %s\n"), id, ctx->ipstr, message);
            _tcsupr(message);

            if (send(ctx->sockfd, (const char *)message, (_tcslen(message) + 1) * sizeof(TCHAR), 0) == -1)
            {
                _ftprintf(stderr, _T("[%u] Failed to send reply message to client <%s>: "), id, ctx->ipstr);
                print_error_ex(_T("send"));
            }
        }
    }
    else
    {
        _ftprintf(stderr, _T("[%u] Failed to send welcome message to client <%s>: "), id, ctx->ipstr);
        print_error_ex(_T("send"));
    }

    InterlockedExchange(&ctx->running, 0);

    _tprintf(_T("[%u] Worker is fired!\n"), id);

    return 0;
}


static int is_idle_worker_context_slot(const void *arg, const void *value)
{
    worker_context_t *ctx;

    assert(arg != NULL);
    (void)value;
    ctx = (worker_context_t *)arg;

    return ctx->running == 0;
}


static int is_active_worker_context_slot(const void *arg, const void *value)
{
    return !is_idle_worker_context_slot(arg, value);
}


static bool spawn_worker_thread(const _TCHAR *ip, socket_t sockfd, dyarr_t workers)
{
    size_t slot = INVALID_SOCKET;
    size_t i;
    worker_context_t *ctx;
    HANDLE thread;
    unsigned thread_id;

    assert(ip != NULL);
    assert(sockfd != INVALID_SOCKET);
    assert(workers != NULL);

    for (i = 0; i < dyarr_size(workers); ++i)
    {
        worker_context_t *elem = dyarr_at(workers, i);
        if (is_idle_worker_context_slot(elem, NULL))
        {
            if (elem->handle != NULL)
            {
                printf("Waiting for worker thread exiting...\n");
                WaitForSingleObject(elem->handle, INFINITE);
                CloseHandle(elem->handle);
                elem->handle = NULL;
            }

            if (elem->sockfd != INVALID_SOCKET)
            {
                closesock(elem->sockfd);
                elem->sockfd = INVALID_SOCKET;
            }

            slot = i;
            break;
        }
    }

    if (slot == INVALID_INDEX)
    {
        if (!dyarr_resize(workers, dyarr_size(workers) + 1))
        {
            fprintf(stderr, "No enough memory!\n");
            return false;
        }

        slot = dyarr_size(workers) - 1;
    }

    ctx = dyarr_at(workers, slot);

    thread = (HANDLE)_beginthreadex(
        NULL,
        0,
        (_beginthreadex_proc_type)worker_routine,
        ctx,
        CREATE_SUSPENDED,
        &thread_id);
    if (thread == NULL)
    {
        fprintf(stderr, "Failed to create worker thread!\n");
        return false;
    }

    ctx->handle = thread;
    ctx->sockfd = sockfd;
    ctx->running = 1;
    _tcscpy(ctx->ipstr, ip);

    printf("Starting working thread [%u]...\n", thread_id);
    printf("Now we have %zu worker threads.\n", dyarr_size(workers));

    ResumeThread(thread);

    return true;
}


int start_server(socket_t sockfd)
{
    struct sockaddr_storage client_addr;
    socklen_t sin_size;
    _TCHAR ipstr[INET6_ADDRSTRLEN];
    socket_t client_sockfd;
    dyarr_t workers = dyarr_new(sizeof(worker_context_t), false, true);
    size_t i;
    int error_code = EXIT_SUCCESS;

    assert(sockfd != INVALID_SOCKET);

    if (workers == NULL)
    {
        fprintf(stderr, "No enough memory!\n");
        return EXIT_FAILURE;
    }

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
            _ftprintf(stdout, _T("Got connection from: %s.\n"), ipstr);
            if (!spawn_worker_thread(ipstr, client_sockfd, workers))
            {
                error_code = EXIT_FAILURE;
                break;
            }
        }
        else
        {
            fprintf(stderr, "inet_ntop failed.\n");
        }
    }

    for (i = 0; i < dyarr_size(workers); ++i)
    {
        worker_context_t *ctx = dyarr_at(workers, i);

        if (ctx->handle != NULL)
        {
            InterlockedExchange(&(ctx->running), 0);

            printf("Waiting for worker thread exiting...\n");
            WaitForSingleObject(ctx->handle, INFINITE);
            CloseHandle(ctx->handle);
            ctx->handle = NULL;
        }

        if (ctx->sockfd != INVALID_SOCKET)
        {
            closesock(ctx->sockfd);
            ctx->sockfd = INVALID_SOCKET;
        }
    }

    dyarr_free(&workers);

    return error_code;
}
#endif


// References:
// Beej's Guide to Network Programming Using Internet Sockets, Ch6.1
// http://www.cnblogs.com/foohack/p/5013272.html
// https://stackoverflow.com/questions/5919996/how-to-detect-reliably-mac-os-x-ios-linux-windows-in-c-preprocessor
