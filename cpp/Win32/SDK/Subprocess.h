#pragma once

#include <functional>
#include <initializer_list>
#include <string>

#define USE_RAII_HANDLE_CLASS

#ifdef USE_RAII_HANDLE_CLASS
#include "Handle.h"
#else
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

using string_type = std::basic_string<TCHAR>;

class Subprocess {
 public:
  struct Config {
    bool IsConsoleApplication = true;
    bool ShowWindow = true;
    DWORD BufferSize = 4096;
    LPCTSTR CurrentDirectory = nullptr;
  };

  Subprocess(LPCTSTR lpcszCommandLine,
             std::function<void(LPVOID, DWORD)> processOutput =
                 std::function<void(LPVOID, DWORD)>(),
             Config config = Config())
      : Subprocess(nullptr, lpcszCommandLine, processOutput, config) {}

  Subprocess(LPCTSTR lpcszApplication, LPCTSTR lpcszArguments,
             std::function<void(LPVOID, DWORD)> processOutput =
                 std::function<void(LPVOID, DWORD)>(),
             Config config = Config())
      : application_(lpcszApplication != nullptr ? lpcszApplication
                                                 : string_type()),
        arguments_(lpcszArguments != nullptr ? lpcszArguments : string_type()),
        processOutput_(processOutput),
#ifndef USE_RAII_HANDLE_CLASS
        stdoutReadPipe_(nullptr),
        stdoutWritePipe_(nullptr),
        childProcess_(nullptr),
        thread_(nullptr),
#endif
        config_(config) {
    Run(config_);
  }

  Subprocess(std::initializer_list<LPCTSTR> arguments,
             std::function<void(LPVOID, DWORD)> processOutput =
                 std::function<void(LPVOID, DWORD)>(),
             Config config = Config())
      : Subprocess(nullptr, arguments, processOutput, config) {}

  Subprocess(LPCTSTR lpcszApplication, std::initializer_list<LPCTSTR> arguments,
             std::function<void(LPVOID, DWORD)> processOutput =
                 std::function<void(LPVOID, DWORD)>(),
             Config config = Config())
      : processOutput_(processOutput),
#ifndef USE_RAII_HANDLE_CLASS
        stdoutReadPipe_(nullptr),
        stdoutWritePipe_(nullptr),
        childProcess_(nullptr),
        thread_(nullptr),
#endif
        config_(config) {
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

    Run(config_);
  }

  ~Subprocess() {
    DWORD dwExitCode;
    Wait(dwExitCode);
  }

  bool Wait(DWORD &dwExitCode);

  string_type GetLastErrorHint() const { return lastErrorHint_; }

 private:
  void Run(const Config &config);

  static unsigned int __stdcall ProcessOutput(void *arg);

  string_type application_;
  string_type arguments_;
  Config config_;
  string_type lastErrorHint_;
#ifdef USE_RAII_HANDLE_CLASS
  Win32Handle<NULL> stdoutReadPipe_;
  Win32Handle<NULL> stdoutWritePipe_;
  Win32Handle<NULL> childProcess_;
  Win32Handle<NULL> thread_;
#else
  HANDLE stdoutReadPipe_;
  HANDLE stdoutWritePipe_;
  HANDLE childProcess_;
  HANDLE thread_;
#endif
  std::function<void(LPVOID, DWORD)> processOutput_;
};
