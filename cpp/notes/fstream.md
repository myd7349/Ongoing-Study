Get a file's size
- [How can I get a file's size in C++?](https://stackoverflow.com/questions/5840148/how-can-i-get-a-files-size-in-c)
- [tellg() function give wrong size of file?](https://stackoverflow.com/questions/22984956/tellg-function-give-wrong-size-of-file)
- [How can I get a file's size in C? ](https://stackoverflow.com/questions/238603/how-can-i-get-a-files-size-in-c)

Read whole file
- [What is the best way to read an entire file into a std::string in C++?](https://stackoverflow.com/questions/116038/what-is-the-best-way-to-read-an-entire-file-into-a-stdstring-in-c)
- [Read whole ASCII file into C++ std::string](https://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring)

Get file size
- [How can I get a file's size in C++?](https://stackoverflow.com/questions/5840148/how-can-i-get-a-files-size-in-c)

```cpp
std::ifstream::pos_type GetFileSize(const char *filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}
```

[Get file size](https://www.bfilipek.com/2019/01/filesize.html)

[Difference between ios::app and ios::ate](https://stackoverflow.com/questions/12929378/difference-between-iosapp-and-iosate)

[C++ Filehandling: Difference between ios::app and ios::ate?](https://stackoverflow.com/questions/10359702/c-filehandling-difference-between-iosapp-and-iosate)

[How to append file in c++ using fstream?](https://stackoverflow.com/questions/23615975/how-to-append-file-in-c-using-fstream)

[How to append to a file with fstream fstream::app flag seems not to work](https://stackoverflow.com/questions/4712192/how-to-append-to-a-file-with-fstream-fstreamapp-flag-seems-not-to-work)

[appending to a file with ofstream](https://stackoverflow.com/questions/26084885/appending-to-a-file-with-ofstream)

[std::ofstream with std::ate not opening at end](https://stackoverflow.com/questions/28999745/stdofstream-with-stdate-not-opening-at-end)
