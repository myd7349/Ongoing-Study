#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <getopt.h>
#else
#include <unistd.h>
#endif


int main(int argc, char *argv[])
{
    const char *host = NULL;
    const char *port = NULL;
    int c;
    int index;

    while ((c = getopt(argc, argv, "h:p:")) != -1)
    {
        switch (c)
        {
        case 'h':
            host = optarg;
            break;
        case 'p':
            port = optarg;
            break;
        case '?':
            puts(
                "Options:\n"
                "  -h <host> Specify host name\n"
                "  -p <port> Specify port number");
            break;
        default:
            exit(EXIT_FAILURE);
            break;
        }
    }

    for (index = optind; index < argc; ++index)
        fprintf(stderr, "Unknown option: %s\n", argv[index]);

    printf("Host: %s:%s\n", host, port);

    return EXIT_SUCCESS;
}


// References:
// https://en.wikipedia.org/wiki/Getopt
// https://www.gnu.org/software/libc/manual/html_node/Example-of-Getopt.html#Example-of-Getopt
// https://stackoverflow.com/questions/5045821/getopt-not-enforcing-required-arguments
