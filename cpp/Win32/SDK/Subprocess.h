#pragma once

#include <functional>
#include <initializer_list>
#include <string>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "Handle.h"

using string_type = std::basic_string<TCHAR>;

class Subprocess {
 public:
  Subprocess(LPCTSTR lpcszCommandLine,
             std::function<void(LPVOID, DWORD)> processOutput =
                 std::function<void(LPVOID, DWORD)>(),
             BOOL bShowWindow = TRUE, DWORD dwBufferSize = 4096)
      : Subprocess(nullptr, lpcszCommandLine, processOutput, bShowWindow,
                   dwBufferSize) {}

  Subprocess(LPCTSTR lpcszApplication, LPCTSTR lpcszArguments,
             std::function<void(LPVOID, DWORD)> processOutput =
                 std::function<void(LPVOID, DWORD)>(),
             BOOL bShowWindow = TRUE, DWORD dwBufferSize = 4096)
      : application_(lpcszApplication != nullptr ? lpcszApplication
                                                 : string_type()),
        arguments_(lpcszArguments != nullptr ? lpcszArguments : string_type()),
        processOutput_(processOutput),
        dwBufferSize_(dwBufferSize) {
    Run(bShowWindow);
  }

  Subprocess(std::initializer_list<LPCTSTR> arguments,
             std::function<void(LPVOID, DWORD)> processOutput =
                 std::function<void(LPVOID, DWORD)>(),
             BOOL bShowWindow = TRUE, DWORD dwBufferSize = 4096)
      : Subprocess(arguments.size() > 0 ? *arguments.begin() : nullptr,
                   std::initializer_list<LPCTSTR>(arguments.size() > 0
                                                      ? arguments.begin() + 1
                                                      : arguments.begin(),
                                                  arguments.end()),
                   processOutput, bShowWindow, dwBufferSize) {}

  Subprocess(LPCTSTR lpcszApplication, std::initializer_list<LPCTSTR> arguments,
             std::function<void(LPVOID, DWORD)> processOutput =
                 std::function<void(LPVOID, DWORD)>(),
             BOOL bShowWindow = TRUE, DWORD dwBufferSize = 4096)
      : processOutput_(processOutput), dwBufferSize_(dwBufferSize) {
    if (arguments.size() >= 1) {
      application_ =
          lpcszApplication != nullptr ? lpcszApplication : string_type();
      for (auto it = arguments.begin(); it != arguments.end(); ++it) {
        if (*it != nullptr) {
          if (!arguments_.empty()) arguments_ += TEXT(' ');

          arguments_ += *it;
        }
      }
    }

    Run(bShowWindow);
  }

  ~Subprocess() {
    DWORD dwExitCode;
    Wait(dwExitCode);
  }

  bool Wait(DWORD &dwExitCode);

 private:
  void Run(BOOL bShowWindow);

  static unsigned int __stdcall ProcessOutput(void *arg);

  string_type application_;
  string_type arguments_;
  string_type lastErrorHint_;
  Win32Handle<NULL> stdoutReadPipe_;
  Win32Handle<NULL> stdoutWritePipe_;
  Win32Handle<NULL> childProcess_;
  DWORD dwBufferSize_;
  std::function<void(LPVOID, DWORD)> processOutput_;
  Win32Handle<NULL> thread_;
};
