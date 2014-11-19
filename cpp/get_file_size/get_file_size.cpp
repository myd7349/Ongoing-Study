// 2014-11-19T13:47+08:00
// This is an example for explaining clause 3.3.10/2 in ISO C++11 standard.
//
// When I was studying an FTP file uploading example(ftpupload.c) in libcurl's
// example directory today, I came across some C code like this:
// (You can find this example on: http://curl.haxx.se/libcurl/c/ftpupload.html)
//struct stat file_info;
//stat(LOCAL_FILE, &file_info);
// I was wondering if I can rewrite them like this in C++:
//stat file_info;
//stat(LOCAL_FILE, &file_info);
// The answer is NO.
#include <iostream>

#include <sys/types.h>
#include <sys/stat.h>

int main()
{
    // Though we are using C++, we can't write code like this:
    //stat fileInfo;
    // Since stat is also a function here, which will hide the class with the same name in this scope.
    // Please refer to clause 3.3.10/2 in ISO C++11 standard or this page:
    // http://stackoverflow.com/questions/23329382/function-and-struct-having-the-same-name-in-c
    struct stat fileInfo;

    int res = stat("get_file_size.cpp", &fileInfo);
    if (res != 0) {
        std::cerr << "Failed to obtain file-status information: " << res << '\n';
        return 1;
    }

    std::cout << "File size: " << fileInfo.st_size << std::endl;

    return 0;
}
