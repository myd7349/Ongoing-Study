// clang-format off
#include <errno.h>
#include <limits.h>
#include <stdlib.h>

#include <cassert>
#include <algorithm>
#include <deque>
#include <iostream>
#include <locale>
#include <string>

#include <tchar.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "../../../../../c/Win32/wconv.h"
#include "../../../../../cpp/strutils.hpp"
// clang-format on

class IStreamReader {
 public:
  virtual ~IStreamReader() {}

  virtual int ReadChar() = 0;
  virtual std::size_t Read(char *buffer, std::size_t bytes) = 0;
};

class PipeStreamReader : public IStreamReader {
 public:
  PipeStreamReader(HANDLE hPipe) : hPipe_(hPipe) {}

  int ReadChar() override {
    char ch;
    if (Read(&ch, 1) == 1) return ch;

    return -1;
  }

  std::size_t Read(char *buffer, std::size_t bytes) override {
    DWORD dwBytesRead;
    if (!ReadFile(hPipe_, buffer, bytes, &dwBytesRead, nullptr)) return 0;

    return dwBytesRead;
  }

 private:
  HANDLE hPipe_;
};

const int LineBufferSize = 256;

class TextReader {
 public:
  TextReader(IStreamReader &streamReader) : streamReader_(streamReader) {}

  std::string ReadLine() {
    std::string line;

    if (!buffer_.empty()) {
      auto it = std::find(buffer_.cbegin(), buffer_.cend(), '\n');
      if (it != buffer_.cend()) {
        line = std::string(buffer_.cbegin(), std::next(it));

        buffer_.erase(buffer_.cbegin(), std::next(it));

        return line;
      } else {
        line += std::string(buffer_.cbegin(), buffer_.cend());
        buffer_.clear();
      }
    }

    assert(buffer_.empty());

    char bytes[LineBufferSize];
    std::size_t bytesRead;

    while ((bytesRead = streamReader_.Read(bytes, sizeof(bytes))) > 0) {
      auto begin = std::cbegin(bytes);
      auto end = begin + bytesRead;

      auto it = std::find(begin, end, '\n');
      if (it == end) {
        line += std::string(bytes, bytesRead);
      } else {
        line += std::string(begin, std::next(it));

        std::copy(std::next(it), end, std::back_inserter(buffer_));

        break;
      }
    }

    return line;
  }

 private:
  IStreamReader &streamReader_;
  std::deque<char> buffer_;
};

inline std::wstring ReadLine(TextReader &textReader) {
  auto line = textReader.ReadLine();
  return Utf8ToWChar(
      TrimRightInPlace(line));  // C#'s StreamWriter uses UTF-8 by default.
}

int _tmain(int argc, _TCHAR *argv[]) {
  if (argc != 2) return 1;

  std::wcin.imbue(std::locale(""));
  std::wcout.imbue(std::locale(""));
  std::wcerr.imbue(std::locale(""));

  std::wcout << L"[CLIENT] Handle passed through cli: " << argv[1] << std::endl;
  std::wcout << L"[CLIENT] Handle get via GetStdHandle(STD_INPUT_HANDLE): "
             << GetStdHandle(STD_INPUT_HANDLE) << std::endl;
  std::wcout << L"[CLIENT] Handle get via GetStdHandle(STD_OUTPUT_HANDLE): "
             << GetStdHandle(STD_OUTPUT_HANDLE) << std::endl;

#ifndef NDEBUG
  std::wcout << L"[CLIENT] Press any key to start!";
  std::wcin.get();
#endif

  ULONG_PTR handle = _tcstoul(argv[1], NULL, 10);
  if (handle == 0 || (handle == ULONG_MAX && errno == ERANGE)) return 1;

  HANDLE hPipe = (HANDLE)handle;

  PipeStreamReader pipeStreamReader(hPipe);
  TextReader textReader(pipeStreamReader);

  std::wstring message;
  do {
    std::wcout << L"[CLIENT] Wait for SYNC..." << std::endl;
    message = ReadLine(textReader);
  } while (message != L"SYNC");

  while ((message = ReadLine(textReader)) != L"")
    std::wcout << L"[CLIENT] Echo: " << message << std::endl;

  // TODO: Should I call:
  // CloseHandle(hPipe);
  // here?

  return 0;
}


// clang-format off
// References:
// [Calling C# code from C++](https://stackoverflow.com/questions/778590/calling-c-sharp-code-from-c)
// [Anonymous Pipes](https://docs.microsoft.com/en-us/windows/win32/ipc/anonymous-pipes)
// [Inter-Process Communication between C# and C++](https://www.codeproject.com/Tips/420582/Inter-Process-Communication-between-Csharp-and-Cpl)
// [Creating a Child Process with Redirected Input and Output](https://docs.microsoft.com/en-us/windows/win32/ProcThread/creating-a-child-process-with-redirected-input-and-output)
// [Anonymous Pipe Operations](https://docs.microsoft.com/en-us/windows/win32/ipc/anonymous-pipe-operations)
// https://github.com/csandker/InterProcessCommunication-Samples
// [Are wchar_t and char16_t the same thing on Windows?](https://stackoverflow.com/questions/53293159/are-wchar-t-and-char16-t-the-same-thing-on-windows/53293817)
// [communication between c++ and c# through pipe](https://stackoverflow.com/questions/1906561/communication-between-c-and-c-sharp-through-pipe)
// [How to work with named pipes (C++ server , C# client)](https://stackoverflow.com/questions/9676343/how-to-work-with-named-pipes-c-server-c-sharp-client)
// clang-format on
