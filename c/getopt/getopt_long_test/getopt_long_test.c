#include <stdio.h>
#include <stdlib.h>

#include <getopt.h>

#ifdef __linux__
#include <unistd.h>
#endif


int main(int argc, char *argv[])
{
    struct option long_options[] =
    {
        { "host", required_argument, NULL, 'H' },
        { "serv", required_argument, NULL, 'S' },
        { "help", no_argument, NULL, 'h' },
        { NULL, 0, NULL, 0 }
    };

    const char *usage =
        "Usage:\n"
        "  getopt_long_test <options>\n\n"
        "Options:\n"
        "  --host,-H Specify host name\n"
        "  --serv,-S Specify serv name\n"
        "  --help,-h Print this message";

    const char *host = NULL;
    const char *serv = NULL;

    int c;
    int option_index = 0;

    while ((c = getopt_long(argc, argv, "H:S:h", long_options, &option_index)) != -1)
    {
        switch (c)
        {
        case 'H':
            host = optarg;
            break;
        case 'S':
            serv = optarg;
            break;
        case 'h':
            puts(usage);
            return EXIT_SUCCESS;
            break;
        case '?':
            exit(EXIT_FAILURE);
            break;
        default:
            fprintf(stderr, "?? getopt_long returned character code 0%o ??\n", c);
            exit(EXIT_FAILURE);
            break;
        }
    }

    if (host == NULL)
    {
        fprintf(stderr, "Required argument for option '--host'\n");
        exit(EXIT_FAILURE);
    }

    if (serv == NULL)
    {
        fprintf(stderr, "Required argument for option '--serv'\n");
        exit(EXIT_FAILURE);
    }

    printf("%s:%s\n", host, serv);

    return EXIT_SUCCESS;
}


// References:
// man:getopt_long
// https://en.wikipedia.org/wiki/Getopt
// https://www.gnu.org/software/libc/manual/html_node/Example-of-Getopt.html#Example-of-Getopt
// https://stackoverflow.com/questions/5045821/getopt-not-enforcing-required-arguments
// https://github.com/libimobiledevice-win32/getopt/blob/master/article.md
