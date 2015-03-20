// 2015-01-09T17:14+08:00

// Shows how to handle Ctrl-C

#include "zhelpers.h"

#include <signal.h>

// Signal handling
// Call s_catch_signals() in your application at startup, and then
// exit your main loop if s_interrupted is ever 1. Works especially
// well with zmq_poll.


#ifdef WIN32
#if 0
#include <windows.h>
static volatile BOOL s_interrupted = FALSE;
static BOOL WINAPI s_signal_handler(DWORD dwCtrlType)
{
    switch (dwCtrlType)
    {
    case CTRL_C_EVENT:
        s_interrupted = TRUE;
        return TRUE;
    default:
        return FALSE;
    }
}
static void s_catch_signals(void)
{
    SetConsoleCtrlHandler(s_signal_handler, TRUE);
}
#else
static volatile sig_atomic_t s_interrupted = 0;
static void s_signal_handler(int signal_value)
{
    s_interrupted = 1;
}

static void s_catch_signals(void)
{
    signal(SIGINT, s_signal_handler);
    signal(SIGTERM, s_signal_handler);
}
#endif
#else
static volatile sig_atomic_t s_interrupted = 0;
static void s_signal_handler(int signal_value)
{
    s_interrupted = 1;
}

static void s_catch_signals(void)
{
    struct sigaction action;
    action.sa_handler = s_signal_handler;
    action.sa_flags = 0;
    sigemptyset(&action.sa_mask);
    sigaction(SIGINT, &action, NULL);
    sigaction(SIGTERM, &action, NULL);
}
#endif

int main(void)
{
    void *context = zmq_ctx_new();
    void *socket = zmq_socket(context, ZMQ_REP);
    zmq_bind(socket, "tcp://*:5555");

    s_catch_signals();
#if 1
    while (1) {
        // Blocking read will exit on a signal
        char buffer[255];
        zmq_recv(socket, buffer, 255, 0);
        if (s_interrupted) {
            printf("W: interrupt received, killing server...\n");
            break;
        }
    }
#else
    while (!s_interrupted) {
        char *message = s_recv(socket);
        if (!message) {
            break;
        }
    }
#endif

    zmq_close(socket);
    zmq_ctx_destroy(context);

#ifdef _MSC_VER
    system("pause");
#endif
    return 0;
}
