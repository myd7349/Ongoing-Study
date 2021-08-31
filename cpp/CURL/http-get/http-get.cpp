#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>

#include <curl/curl.h>
#include <yyjson.h>

#ifdef WCONV_SUPPORT
# include "wconv.h"
#endif


#define log_error_no_source_info(fmt, ...) std::fprintf(stderr, fmt, __VA_ARGS__)

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
        error_message_length = std::strlen(error_message); \
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
        return nullptr; \
    } \
} while (0)

#define curl_easy_setopt_checked(curl, option, ...) curl_checked(curl_easy_setopt, (curl), (option), __VA_ARGS__)

#define curl_easy_perform_checked(curl) curl_checked(curl_easy_perform, (curl))

#define curl_easy_getinfo_checked(curl, info, ...) curl_checked(curl_easy_getinfo, (curl), (info), __VA_ARGS__)


size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    assert(userdata != nullptr);

    std::string *buffer = static_cast<std::string *>(userdata);

    size_t bytes { size * nmemb };
    buffer->append(ptr, bytes);

    return bytes;
}


std::unique_ptr<std::string> http_get(const char *url, long *response_code)
{
    assert(url != nullptr);

    CURL *curl = curl_easy_init();
    if (curl == nullptr)
    {
        log_error("curl_easy_init failed!\n");
        return nullptr;
    }

    char error_message[CURL_ERROR_SIZE];
    size_t error_message_length;
    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, error_message);

    CURLcode result;

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
    std::unique_ptr<std::string> response = std::make_unique<std::string>();
    curl_easy_setopt_checked(curl, CURLOPT_WRITEDATA, response.get());

    // Run our HTTP GET command, capture the HTTP response code, and clean up.
    curl_easy_perform_checked(curl);

    curl_easy_getinfo_checked(curl, CURLINFO_RESPONSE_CODE, response_code);

    curl_easy_cleanup(curl);

    return response;
}


std::string json_to_string(yyjson_doc *json)
{
    yyjson_write_flag write_flags = YYJSON_WRITE_PRETTY | YYJSON_WRITE_ESCAPE_UNICODE;
    char *buffer = yyjson_write(json, write_flags, 0);
    if (buffer != nullptr)
    {
        std::string json_string(buffer);
        std::free(buffer);
        return json_string;
    }

    return "";
}


void dump_response(const std::string &response)
{
    yyjson_doc *json = yyjson_read(response.c_str(), response.length(), 0);
    if (json != nullptr)
    {
        std::cout << json_to_string(json);
        yyjson_doc_free(json);
    }
    else
    {
#ifdef WCONV_SUPPORT
        std::cout << Utf8ToAnsi(response);
#elif 1
        std::cout << response;
#elif 0
        std::copy(response.cbegin(), response.cend(), std::ostream_iterator<char>(std::cout));
#else
        for (auto ch : response)
            std::cout << ch;
#endif
    }
}


void easy_http_get(const char *url)
{
    long http_code;
    std::unique_ptr<std::string> response = http_get(url, &http_code);
    if (response != nullptr)
    {
        if (http_code != 200)
            std::cout << "HTTP code: " << http_code << '\n';

        dump_response(*response);
    }
}


int main(int argc, char **argv)
{
    if (argc <= 1)
    {
#ifdef NDEBUG
        std::cout << "Usage:\n    http-get <url>...\n";
#else
        easy_http_get("http://date.jsontest.com/");
#endif
    }
    else
    {
        for (int i = 1; i < argc; i++)
            easy_http_get(argv[i]);
    }

    return EXIT_SUCCESS;
}


// References:
// [curl_jsoncpp_example.cpp](https://gist.github.com/connormanning/41efa6075515019e499c)
// https://curl.se/libcurl/c/CURLOPT_ERRORBUFFER.html
// https://curl.se/libcurl/c/CURLINFO_RESPONSE_CODE.html
// https://github.com/ibireme/yyjson/blob/master/doc/API.md#mutable-and-immutable
// [How do I print out the contents of a vector?](https://stackoverflow.com/questions/10750057/how-do-i-print-out-the-contents-of-a-vector)
