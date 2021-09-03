#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <curl/curl.h>

#include "strdup.h"

#ifdef ENABLE_WCONV
# include "wconv.h"
#endif


#define log_error_no_source_info(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__)

#define log_error(fmt, ...) log_error_no_source_info("%s(%d)> " fmt, __FILE__, __LINE__, __VA_ARGS__)

#define streq(s1, s2) (strcmp((s1), (s2)) == 0)


typedef enum
{
    UNESCAPE,
    ESCAPE,
} method_t;


char *url_escape(const char *url, size_t length)
{
    char *escaped_url;
#ifdef AVOID_CURL_FREE_OUTSIDE
    char *escaped_url_dup;
#endif

    CURL *curl = curl_easy_init();
    if (curl != NULL)
    {
        escaped_url = curl_easy_escape(curl, url, (int)length);
#ifdef AVOID_CURL_FREE_OUTSIDE
        escaped_url_dup = strdup(escaped_url);
        curl_free(escaped_url);
        curl_easy_cleanup(curl);
        return escaped_url_dup;
#else
        curl_easy_cleanup(curl); // Is it OK to call curl_free later?
        return escaped_url; // Call curl_free later.
#endif
    }

    return NULL;
}


char *url_unescape(const char *escaped_url, size_t length, size_t *out_length)
{
    char *url;
#ifdef AVOID_CURL_FREE_OUTSIDE
    char *url_dup;
#endif
    int out_length_i;

    CURL *curl = curl_easy_init();
    if (curl != NULL)
    {
        url = curl_easy_unescape(curl, escaped_url, (int)length, &out_length_i);
        if (out_length != NULL)
            *out_length = (size_t)out_length_i;

#ifdef AVOID_CURL_FREE_OUTSIDE
        url_dup = strdup(url);
        curl_free(url);
        curl_easy_cleanup(curl);
        return url_dup;
#else
        curl_easy_cleanup(curl); // Is it OK to call curl_free later?
        return url; // Call curl_free later.
#endif
    }

    return NULL;
}


#ifdef AVOID_CURL_FREE_OUTSIDE
# define url_free(url) free((url))
#else
# define url_free(url) curl_free((url))
#endif


void print_usage(void)
{
    puts(
        "pctutil [--method METHOD] [--url URL]"
#ifdef ENABLE_WCONV
        " [--utf8]"
#endif
        "\n\n"
        "URL percent-encoding/decoding utility.\n"
        "\n"
        "Optional arguments:\n"
        "    --method,-m {unescape,escape} Specify the operation\n"
        "    --url,-u    URL               Specify the URL\n"
#ifdef ENABLE_WCONV
        "    --utf8                        Enable UTF-8 encoding\n"
#endif
        "    --help,-h                     Show this help message");
}


int parse_arguments(int argc, char *argv[], method_t *method, const char **url, int *utf8)
{
    int help_wanted = 0;
    int i;

    for (i = 1; i < argc; i++)
    {
        if (streq(argv[i], "--method") || streq(argv[i], "-m"))
        {
            if (i + 1 < argc)
            {
                ++i;

                if (streq(argv[i], "unescape"))
                {
                    *method = UNESCAPE;
                }
                else if (streq(argv[i], "escape"))
                {
                    *method = ESCAPE;
                }
                else
                {
                    printf("Unrecognized method \"%s\". Only \"unescape\" and \"escape\" are supported.\n\n", argv[i]);
                    help_wanted = 1;
                    break;
                }
            }
            else
            {
                puts("Missing argument for --method/-m.\n");
                help_wanted = 1;
                break;
            }
        }
        else if (streq(argv[i], "--url") || streq(argv[i], "-u"))
        {
            if (i + 1 < argc)
            {
                ++i;
                *url = argv[i];
            }
            else
            {
                puts("Missing argument for --url/-u.\n");
                help_wanted = 1;
                break;
            }
        }
#ifdef ENABLE_WCONV
        else if (streq(argv[i], "--utf8"))
        {
            *utf8 = 1;
        }
#endif
        else if (streq(argv[i], "--help") || streq(argv[i], "-h"))
        {
            help_wanted = 1;
            break;
        }
        else
        {
            printf("Unrecognized argument: %s.\n\n", argv[i]);
            help_wanted = 1;
            break;
        }
    }

    if (help_wanted)
    {
        print_usage();
        return 0;
    }

    return 1;
}


void handle_url(const char *url, method_t method, int utf8)
{
    char *out_url;
    char *url_utf8;
    char *url_ansi;

    if (utf8)
    {
#ifdef ENABLE_WCONV
        switch (method)
        {
        case UNESCAPE:
            url_utf8 = url_unescape(url, 0, NULL);
            if (url_utf8 != NULL)
            {
                url_ansi = utf8_to_ansi(url_utf8);
                if (url_ansi != NULL)
                {
                    printf("%s", url_ansi);
                    wconv_free(url_ansi);
                }

                url_free(url_utf8);
            }
            break;
        case ESCAPE:
            url_utf8 = ansi_to_utf8(url);
            if (url_utf8 != NULL)
            {
                out_url = url_escape(url_utf8, 0);
                if (out_url != NULL)
                {
                    printf("%s", out_url);
                    url_free(out_url);
                }

                wconv_free(url_utf8);
            }
            break;
        default:
            assert(0);
            break;
        }
#endif
    }
    else
    {
        switch (method)
        {
        case UNESCAPE:
            out_url = url_unescape(url, 0, NULL);
            if (out_url != NULL)
            {
                printf("%s", out_url);
                url_free(out_url);
            }
            break;
        case ESCAPE:
            out_url = url_escape(url, 0);
            if (out_url != NULL)
            {
                printf("%s", out_url);
                url_free(out_url);
            }
            break;
        default:
            assert(0);
            break;
        }
    }
}


int main(int argc, char *argv[])
{
    method_t method = DEFAULT_METHOD;
    const char *url = NULL;
    int utf8 = 0;

#ifdef HAVE_GETLINE
    char *line;
    size_t line_length;
#else
    char line[MAXMIMUM_LINE_LENGTH];
#endif
    char *newline;

    CURLcode result = curl_global_init(CURL_GLOBAL_ALL);
    if (result != CURLE_OK)
    {
        log_error("curl_global_init failed!\n");
        return EXIT_FAILURE;
    }

    if (parse_arguments(argc, argv, &method, &url, &utf8))
    {
        if (url != NULL)
        {
            handle_url(url, method, utf8);
        }
        else
        {
#ifdef HAVE_GETLINE
            while (getline(&line, &line_length, stdin) > 0)
            {
                newline = strrchr(line, '\n');
                if (newline != NULL)
                    *newline = '\0';

                handle_url(line, method, utf8);
                putchar('\n');
                free(line);        
            }

            free(line);
#else
            while (fgets(line, MAXMIMUM_LINE_LENGTH, stdin) != NULL)
            {
                newline = strrchr(line, '\n');
                if (newline != NULL)
                    *newline = '\0';

                handle_url(line, method, utf8);
                putchar('\n');
            }
#endif
        }
    }

    curl_global_cleanup();

    return EXIT_SUCCESS;
}


// References:
// [When is curl_global_init() necessary at all?](https://stackoverflow.com/questions/6087886/when-is-curl-global-init-necessary-at-all/6087988)
// https://curl.se/libcurl/c/curl_global_init.html
// https://curl.se/libcurl/c/curl_global_cleanup.html
// https://curl.se/libcurl/c/libcurl.html
// [How to cleanup definitely a curl handle?](https://stackoverflow.com/questions/53882598/how-to-cleanup-definitely-a-curl-handle)
// [Getting a curl handle to use curl_easy_escape in libcurl](https://stackoverflow.com/questions/41673971/getting-a-curl-handle-to-use-curl-easy-escape-in-libcurl)
// https://curl.se/libcurl/c/curl_easy_escape.html
// https://curl.se/libcurl/c/curl_easy_unescape.html
// [pointer to a const pointer to an int](https://stackoverflow.com/questions/16720921/pointer-to-a-const-pointer-to-an-int)
// https://github.com/danmar/checkheaders/blob/master/src/main.cpp
// https://en.cppreference.com/w/c/experimental/dynamic/getline
