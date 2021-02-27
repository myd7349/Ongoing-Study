1.

2018-08-16T09:34+08:00

https://stackoverflow.com/questions/44792526/differenence-among-open-open-and-fopen-with-regard-to-msvc-compiler

    For the Windows API, you can use _open_osfhandle() to create a FILE * from a HANDLE, and _get_osfhandle() to get the HANDLE from the FILE *. However, in both cases, the handle will be owned by the FILE *.
    
    For the POSIX API, you can use fdopen() to create a FILE * from a int file descriptor, and you can use fileno() to get the int file descriptor from a FILE *. Again, in both cases the file is owned by the FILE *.

2.

2019-05-24T18:41+08:00

stderr seems to be buffered on recent windows.

https://github.com/google/glog/blob/ba8a9f6952d04d1403b97df24e6836227751454e/src/logging_unittest.cc#L184

3.

https://github.com/google/glog/blob/ba8a9f6952d04d1403b97df24e6836227751454e/src/googletest.h

```c
// Return the size (in bytes) of a file
static inline size_t GetFileSize(FILE * file) {
  fseek(file, 0, SEEK_END);
  return static_cast<size_t>(ftell(file));
}
// Read the entire content of a file as a string
static inline string ReadEntireFile(FILE * file) {
  const size_t file_size = GetFileSize(file);
  char * const buffer = new char[file_size];

  size_t bytes_last_read = 0;  // # of bytes read in the last fread()
  size_t bytes_read = 0;       // # of bytes read so far

  fseek(file, 0, SEEK_SET);

  // Keep reading the file until we cannot read further or the
  // pre-determined file size is reached.
  do {
    bytes_last_read = fread(buffer+bytes_read, 1, file_size-bytes_read, file);
    bytes_read += bytes_last_read;
  } while (bytes_last_read > 0 && bytes_read < file_size);

  const string content = string(buffer, buffer+bytes_read);
  delete[] buffer;

  return content;
}
```

https://stackoverflow.com/questions/33327720/how-to-use-fread-to-read-the-entire-file-in-a-loop

>Note that this differs from the underlying read(2) POSIX system call. read() can return less than a full buffer if interrupted, or after a packet from a socket, or after a line on a line-buffered tty, and stuff like that. fread() keeps calling read until the buffer is full or it reaches EOF.

4.

https://github.com/google/glog/blob/ba8a9f6952d04d1403b97df24e6836227751454e/src/signalhandler.cc#L85-L86

The class is used for formatting error messages.  We don't use printf() as it's not async signal safe.

UNPv1 Ch5.9:
>警告：在信号处理函数中调用诸如 printf 这样的标准 I/O 函数是不合适的，其原因将在 11.18 节讨论。
>https://stackoverflow.com/questions/25327519/how-to-send-udp-packet-every-1-ms

5.

Read a file line by line:

https://github.com/google/glog/blob/ba8a9f6952d04d1403b97df24e6836227751454e/src/symbolize.cc#L401-L444

UNPv1

6.

https://stackoverflow.com/questions/14543443/in-c-how-do-you-redirect-stdin-stdout-stderr-to-files-when-making-an-execvp-or

cpp/Google/glog/glog_src_playground/captured_stream.hpp

7.

2019-01-25T13:33+08:00

filecore.cpp

```c
ULONGLONG CStdioFile::GetLength() const
{
   ASSERT_VALID(this);

   LONG nCurrent;
   LONG nLength;
   LONG nResult;

   nCurrent = ftell(m_pStream);
   if (nCurrent == -1)
      AfxThrowFileException(CFileException::invalidFile, _doserrno,
         m_strFileName);

   nResult = fseek(m_pStream, 0, SEEK_END);
   if (nResult != 0)
      AfxThrowFileException(CFileException::badSeek, _doserrno,
         m_strFileName);

   nLength = ftell(m_pStream);
   if (nLength == -1)
      AfxThrowFileException(CFileException::invalidFile, _doserrno,
         m_strFileName);
   nResult = fseek(m_pStream, nCurrent, SEEK_SET);
   if (nResult != 0)
      AfxThrowFileException(CFileException::badSeek, _doserrno,
         m_strFileName);

   return nLength;
}
```

8. snprintf and vsnprintf

https://github.com/google/glog/blob/ba8a9f6952d04d1403b97df24e6836227751454e/src/windows/port.h#L118-L128

https://github.com/google/glog/blob/master/src/windows/port.cc

9. fopen for utf-8

https://github.com/ArtifexSoftware/mupdf/blob/b10c81f8d278534b277d181436d5b8e8a9723af9/source/fitz/time.c#L84-L108

10. fmemopen for Windows

https://github.com/NimbusKit/MemoryMapping

https://stackoverflow.com/questions/12249610/c-create-file-in-memory

https://stackoverflow.com/questions/7307955/is-there-fmemopen-in-mingw

https://github.com/kespindler/python-tesseract/blob/master/util-fmemopen.c

https://github.com/martinh/libconfuse/blob/master/src/fmemopen.c

https://sourceware.org/git/?p=glibc.git;a=blob;f=libio/fmemopen.c;h=c2c67c112063084bc1ef61a3e1ca59bebeeef087;hb=HEAD

https://github.com/njriasan/graphene-docker/blob/aa0a0dcc893a3865345c26a78299326cbc4c3e9c/graphene/LibOS/glibc-2.19/libio/fmemopen.c

https://sourcegraph.com/github.com/DanBloomberg/leptonica/-/blob/src/utils2.c#L1896:1-1896:20

11.

https://github.com/erikd/libsndfile/blob/master/src/file_io.c

https://github.com/GNOME/glib/blob/master/glib/gstdio.c

12.

https://github.com/jmcnamara/libxlsxwriter/commit/37656389c8a7dcd48a8fc7479f77c77519a73416

13.

[```fread``` returns number of objects read, not number of bytes](https://stackoverflow.com/questions/28398255/fread-return-value-in-c)

```c
// Ongoing-Study/cpp/OpenGL/opengl-tutorial/common/texture.cpp
unsigned char header[124];

if ((readBytes = fread(header, sizeof(header), 1, file)) != sizeof(header)) { // Oops!
  fprintf(stderr, "Unexpected DDS header size: %zu: ", readBytes);
  return 0;
}
```

14.

[c++: subprocess output to stdin](https://stackoverflow.com/questions/8438277/c-subprocess-output-to-stdin)

Internally, `popen(<command>)` is interpreted as:
> cmd /c <command>

If `<command>` contains spaces in it, quote the whole command just before passing it to `popen`.


[Creating a Child Process with Redirected Input and Output](https://docs.microsoft.com/en-us/windows/win32/procthread/creating-a-child-process-with-redirected-input-and-output)

[Using a handle to collect output from CreateProcess()](https://stackoverflow.com/questions/2674237/using-a-handle-to-collect-output-from-createprocess)

[launch an exe/process with stdin stdout and stderr?](https://stackoverflow.com/questions/5485923/launch-an-exe-process-with-stdin-stdout-and-stderr/39648986)

15.

[fgets to read line by line in files](https://stackoverflow.com/questions/21180248/fgets-to-read-line-by-line-in-files)
```c
    while (fgets(line, MAX_LINE_SIZE, fp) != NULL)
        ++col;
```

[fwrite vs stdout](https://stackoverflow.com/questions/17259250/fwrite-doesnt-print-anything-to-stdout)
```
char s[5] = { 'H', 'e', 'l', 'l', 'o' };
fwrite(s, 1, 5, stdout);
fflush(stdout);
```

https://github.com/microsoft/vcpkg/blob/f1bef4aa7ca7e2a6ea4f5dfe4850d95fce60b431/toolsrc/src/vcpkg/base/system.print.cpp#L8

16.

[C 语言中为什么没有直接提供二进制数的输出？](https://www.zhihu.com/question/438434182)

[Is there a printf converter to print in binary format?](https://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format)

[Binary representation of a given number](https://www.geeksforgeeks.org/binary-representation-of-a-given-number/)

[Binary representation in C](https://stackoverflow.com/questions/8372646/binary-representation-in-c)

17.

[Create temporary file in C, MS Windows system](https://stackoverflow.com/questions/9717271/create-temporary-file-in-c-ms-windows-system)