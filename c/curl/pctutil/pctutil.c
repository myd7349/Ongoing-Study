#include <curl/curl.h>

int main(void)
{
    curl_global_init(CURL_GLOBAL_ALL);
    curl_global_cleanup();

    return 0;
}