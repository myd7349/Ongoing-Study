#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <curl/curl.h>
#include <yyjson.h>

#include "dynamic_array.h"


#define log_error_no_source_info(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__)

#define log_error(fmt, ...) log_error_no_source_info("%s(%d)> " fmt, __FILE__, __LINE__, __VA_ARGS__)

#define stringify(x) #x

#define curl_checked(func, curl, ...) \
do \
{ \
    error_message[0] = '\0'; \
    result = (func)((curl), __VA_ARGS__); \
    if (result != CURLE_OK) \
    { \
        log_error("%s failed(%d): ", stringify(func), result); \
        error_message_length = strlen(error_message); \
        if (error_message_length > 0) \
        { \
            log_error_no_source_info("%s%s", \
                error_message, \
                ((error_message[error_message_length - 1] != '\n') ? "\n" : "")); \
        } \
        else \
        { \
            log_error_no_source_info("%s\n", curl_easy_strerror(result)); \
        } \
        \
        curl_easy_cleanup(curl); \
        dyarr_free(&buffer); \
        return NULL; \
    } \
} while (0)

#define curl_easy_setopt_checked(curl, option, ...) curl_checked(curl_easy_setopt, (curl), (option), __VA_ARGS__)

#define curl_easy_perform_checked(curl) curl_checked(curl_easy_perform, (curl))

#define curl_easy_getinfo_checked(curl, info, ...) curl_checked(curl_easy_getinfo, (curl), (info), __VA_ARGS__)


size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    dyarr_t buffer = (dyarr_t)userdata;
    size_t bytes = size * nmemb;

    assert(buffer != NULL);

    dyarr_append(buffer, ptr, bytes);

    return bytes;
}


dyarr_t http_get(const char *url, long *response_code)
{
    CURL *curl;
    CURLcode result;
    char error_message[CURL_ERROR_SIZE];
    size_t error_message_length;
    dyarr_t buffer;

    assert(url != NULL);

    buffer = dyarr_new(1, false, false);
    if (buffer == NULL)
    {
        log_error("Out of memory!\n");
        return NULL;
    }

    curl = curl_easy_init();
    if (curl == NULL)
    {
        log_error("curl_easy_init failed!\n");
        dyarr_free(&buffer);
        return NULL;
    }

    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, error_message);

    // Set remote URL.
    curl_easy_setopt_checked(curl, CURLOPT_URL, url);

    // Don't bother trying IPv6, which would increase DNS resolution time.
    curl_easy_setopt_checked(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);

    // Don't wait forever, time out after 30 seconds.
    curl_easy_setopt_checked(curl, CURLOPT_TIMEOUT, 30);

    // Follow HTTP redirects if necessary.
    curl_easy_setopt_checked(curl, CURLOPT_FOLLOWLOCATION, 1L);

    // Hook up data handling function.
    curl_easy_setopt_checked(curl, CURLOPT_WRITEFUNCTION, write_callback);

    // Hook up data container (will be passed as the last parameter to the
    // callback handling function).  Can be any pointer type, since it will
    // internally be passed as a void pointer.
    curl_easy_setopt_checked(curl, CURLOPT_WRITEDATA, buffer);

    // Run our HTTP GET command, capture the HTTP response code, and clean up.
    curl_easy_perform_checked(curl);

    curl_easy_getinfo_checked(curl, CURLINFO_RESPONSE_CODE, response_code);

    curl_easy_cleanup(curl);

    return buffer;
}


char *json_to_string(yyjson_doc *json)
{
    char *json_string;

    yyjson_write_flag write_flags = YYJSON_WRITE_PRETTY | YYJSON_WRITE_ESCAPE_UNICODE;
    json_string = yyjson_write(json, write_flags, 0);

    return json_string;
}


void dump_raw(dyarr_t response)
{
    char *data = dyarr_data(response);
    size_t length = dyarr_size(response);
    size_t i;

    for (i = 0; i < length; ++i)
        putchar(data[i]);
}


void dump_response(dyarr_t response)
{
    yyjson_doc *json = yyjson_read(dyarr_data(response), dyarr_size(response), 0);
    if (json != NULL)
    {
        char *json_string = json_to_string(json);
        if (json_string != NULL)
        {
            printf("%s", json_string);
            free(json_string);
        }

        yyjson_doc_free(json);
    }
    else
    {
        dump_raw(response);
    }
}


void easy_http_get(const char *url)
{
    dyarr_t response;
    long http_code;

    response = http_get(url, &http_code);
    if (response != NULL)
    {
        if (http_code != 200)
            printf("HTTP code: %d\n", http_code);

        dump_response(response);

        dyarr_free(&response);
    }
}


int main(int argc, char **argv)
{
    int i;
    CURLcode result = curl_global_init(CURL_GLOBAL_ALL);
    if (result != CURLE_OK)
    {
        log_error("curl_global_init failed!\n");
        return EXIT_FAILURE;
    }

    if (argc <= 1)
    {
#ifdef NDEBUG
        printf("Usage:\n    http-get <url>...\n");
#else
        easy_http_get("http://date.jsontest.com/");
#endif
    }
    else
    {
        for (i = 1; i < argc; i++)
            easy_http_get(argv[i]);
    }

    curl_global_cleanup();

    return EXIT_SUCCESS;
}


// References:
// [curl_jsoncpp_example.cpp](https://gist.github.com/connormanning/41efa6075515019e499c)
// https://curl.se/libcurl/c/CURLOPT_ERRORBUFFER.html
// https://curl.se/libcurl/c/CURLINFO_RESPONSE_CODE.html
// https://github.com/ibireme/yyjson/blob/master/doc/API.md#mutable-and-immutable
// [When is curl_global_init() necessary at all?](https://stackoverflow.com/questions/6087886/when-is-curl-global-init-necessary-at-all/6087988)
// https://curl.se/libcurl/c/curl_global_init.html
// https://curl.se/libcurl/c/curl_global_cleanup.html
// https://curl.se/libcurl/c/libcurl.html
// [How to cleanup definitely a curl handle?](https://stackoverflow.com/questions/53882598/how-to-cleanup-definitely-a-curl-handle)
// [how to properly reuse a curl handle](https://stackoverflow.com/questions/14911156/how-to-properly-reuse-a-curl-handle)
