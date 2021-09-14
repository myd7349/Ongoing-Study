#include <cstdlib>
#include <iostream>
#include <string>

#include <cpr/cpr.h>
#include <pystring/pystring.h>
#include <yyjson.h>

#ifdef WCONV_SUPPORT
# include "wconv.h"
#endif


#ifndef WCONV_SUPPORT
# define Utf8ToAnsi(s) (s)
#endif


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


void dump_response(cpr::Response response)
{
    if (pystring::startswith(response.header["content-type"], "application/json"))
    {
        const std::string &content = response.text;
        yyjson_doc *json = yyjson_read(content.c_str(), content.length(), 0);
        if (json != nullptr)
        {
            std::cout << Utf8ToAnsi(json_to_string(json));
            yyjson_doc_free(json);
            return;
        }
    }

    std::cout << Utf8ToAnsi(response.text);
}


void easy_http_get(const char *url)
{
    cpr::Response response = cpr::Get(cpr::Url(url));
    if (response.status_code != 200)
        std::cout << "HTTP code: " << response.status_code << '\n';
    
    dump_response(response);
}


int main(int argc, char **argv)
{
    if (argc <= 1)
    {
#ifdef NDEBUG
        std::cout << "Usage:\n    http-get <url>...\n";
#else
        easy_http_get("https://api.github.com/repos/myd7349/Ongoing-Study/contributors?anon=true&key=value");
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
// https://github.com/libcpr/cpr
// https://gist.github.com/whoshuu/2dc858b8730079602044
