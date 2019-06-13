#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <netinet/in.h>
#include <signal.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


#define MAXLINE (1024)


void sigchld_handler(int s)
{
    pid_t pid;
    int stat;

#if 0
    pid = wait(&stat);
//#ifndef NDEBUG
    printf("Child %d terminated.\n", (int)pid);
//#endif
#else
    while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
//#ifndef NDEBUG
        printf("Child %d terminated.\n", (int)pid);
//#endif
#endif
}


ssize_t writen(int fd, const void *buf, size_t n)
{
    size_t nleft;
    ssize_t nwritten;
    const char *ptr;

    ptr = buf;
    nleft = n;

    while (nleft > 0)
    {
        if ((nwritten = write(fd, ptr, nleft)) <= 0)
        {
            if (nwritten < 0 && errno == EINTR)
                nwritten = 0;
            else
                return -1;
        }

        nleft -= nwritten;
        ptr += nwritten;
    }

    return n;
}


void str_echo(int sockfd)
{
    ssize_t n;
    char buf[MAXLINE];

    while (1)
    {
        n = read(sockfd, buf, MAXLINE);
        if (n > 0)
        {
            writen(sockfd, buf, n);
        }
        else if (n == 0)
        {
            break;
        }
        else if (n < 0 && errno != EINTR)
        {
            fprintf(stderr, "read failed(%d): %s\n", errno, strerror(errno));
            break;
        }
    }
}


int main(int argc, char **argv)
{
    int listenfd;
    int connfd;
    int res;
    socklen_t addrlen;
    struct sockaddr_in cliaddr;
    struct sockaddr_in servaddr;
    uint16_t port;

    pid_t childpid;

    struct sigaction sa;

    if (argc != 2)
    {
        puts("Usage:\n    a.out <port>");
        return EXIT_FAILURE;
    }

    sa.sa_handler = sigchld_handler;
    sigemptyset(&sa.sa_mask);
#if 1
    sa.sa_flags = SA_RESTART;
#else
    // If the client presses Ctrl+C, this app will print:
    //   accept failed(4): Interrupted system call
    sa.sa_flags = 0;
#endif

    if (sigaction(SIGCHLD, &sa, NULL) == -1)
    {
        fprintf(stderr, "sigaction failed(%d): %s\n", errno, strerror(errno));
        return EXIT_FAILURE;
    }

    port = (uint16_t)atoi(argv[1]);

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1)
    {
        fprintf(stderr, "socket failed(%d): %s\n", errno, strerror(errno));
        return EXIT_FAILURE;
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    res = bind(listenfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));
    if (res == -1)
    {
        fprintf(stderr, "bind failed(%d): %s\n", errno, strerror(errno));
        close(listenfd);
        return EXIT_FAILURE;
    }

    res = listen(listenfd, SOMAXCONN);
    if (res == -1)
    {
        fprintf(stderr, "listen failed(%d): %s\n", errno, strerror(errno));
        close(listenfd);
        return EXIT_FAILURE;
    }

    while (1)
    {
        addrlen = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &addrlen);

        if (connfd == -1)
        {
            if (errno == EINTR)
            {
                fprintf(stderr, "accept failed(%d): %s, will try again.\n", errno, strerror(errno));
                continue;
            }
            else
            {
                fprintf(stderr, "accept failed(%d): %s\n", errno, strerror(errno));
                break;
            }
        }

        childpid = fork();
        if (childpid == 0) // child process
        {
            close(listenfd);
            str_echo(connfd);
#if 1
            close(connfd);
            return 0;
#else
            exit(0); // Ch5.10
#endif
        }
        else
        {
            close(connfd); // parent closes connected socket
        }
    }

    close(listenfd);

    return 0;
}


// References:
// UNPv1, Ch5.2, Ch5.9, Ch5.10
// https://stackoverflow.com/questions/25327519/how-to-send-udp-packet-every-1-ms
