#include <cassert>

#include <process.h>
#include <vector>

#include "Subprocess.h"

void Subprocess::Run(const Config &config) {
  assert(childProcess_ == NULL);

  if (processOutput_) {
    SECURITY_ATTRIBUTES sa;

    ZeroMemory(&sa, sizeof(sa));
    // Set the bInheritHandle flag so pipe handles are inherited.
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = NULL;

    // Create a pipe for the child process's STDOUT.
    if (!CreatePipe(&stdoutReadPipe_, &stdoutWritePipe_, &sa, 0)) {
      lastErrorHint_ = TEXT("CreatePipe");
      return;
    }

    // Ensure the read handle to the pipe for STDOUT is not inherited.
    if (!SetHandleInformation(stdoutReadPipe_, HANDLE_FLAG_INHERIT, 0)) {
      lastErrorHint_ = TEXT("SetHandleInformation");
      stdoutReadPipe_.Close();
      stdoutWritePipe_.Close();
      return;
    }
  }

  STARTUPINFO si{};
  si.cb = sizeof(STARTUPINFO);
  si.hStdInput = NULL;

  if (stdoutWritePipe_) {
    si.hStdOutput = stdoutWritePipe_;
    si.hStdError = stdoutWritePipe_;
    si.dwFlags |= STARTF_USESTDHANDLES;
  }

  if (!config.IsConsoleApplication && !config.ShowWindow) {
    si.wShowWindow = SW_HIDE;
    si.dwFlags |= STARTF_USESHOWWINDOW;
  }

  PROCESS_INFORMATION pi{};

  DWORD dwCreationFlags = 0;
  if (config.IsConsoleApplication && !config.ShowWindow)
    dwCreationFlags |= CREATE_NO_WINDOW;

  BOOL bSuccess = CreateProcess(
      application_.empty() ? nullptr : &application_[0],
      arguments_.empty() ? nullptr : &arguments_[0], NULL, NULL, TRUE,
      dwCreationFlags, NULL, config.CurrentDirectory, &si, &pi);
  if (!bSuccess) {
    stdoutReadPipe_.Close();
    stdoutWritePipe_.Close();
    lastErrorHint_ = TEXT("CreateProcess");
    return;
  }

  CloseHandle(pi.hThread);

  childProcess_.Attach(pi.hProcess);

  if (processOutput_) {
    HANDLE hThread =
        (HANDLE)_beginthreadex(NULL, 0, ProcessOutput, this, 0, NULL);
    if (hThread != NULL) thread_.Attach(hThread);
  }
}

bool Subprocess::Wait(DWORD &dwExitCode) {
  if (!childProcess_) return false;

  switch (WaitForSingleObject(childProcess_, INFINITE)) {
    case WAIT_TIMEOUT:
      lastErrorHint_ = TEXT("WaitForSingleObject");
      return false;
      break;
    case WAIT_FAILED:
      lastErrorHint_ = TEXT("WaitForSingleObject");
      return false;
      break;
    case WAIT_OBJECT_0:
      if (!GetExitCodeProcess(childProcess_, &dwExitCode))
        lastErrorHint_ = TEXT("GetExitCodeProcess");

      childProcess_.Close();
      stdoutWritePipe_.Close();  // Close it, otherwise ProcessOutput
                                 // will hang with `ReadFile`.
      break;
    default:
      assert(FALSE);
      break;
  }

  if (thread_) {
    WaitForSingleObject(thread_, INFINITE);
    thread_.Close();
  }

  if (stdoutReadPipe_) stdoutReadPipe_.Close();

  return true;
}

unsigned int __stdcall Subprocess::ProcessOutput(void *arg) {
  assert(arg != nullptr);

  Subprocess *context = (Subprocess *)arg;

  BOOL bSuccess;

  std::vector<BYTE> buffer(
      context->config_.BufferSize > 0 ? context->config_.BufferSize : 4096);
  DWORD dwRead;

  while (TRUE) {
    bSuccess = ReadFile(context->stdoutReadPipe_, buffer.data(),
                        static_cast<DWORD>(buffer.size()), &dwRead, NULL);
    if (!bSuccess || dwRead == 0) break;

    if (context->processOutput_) context->processOutput_(buffer.data(), dwRead);
  }

  return 0;
}

// clang-format off
// References:
// Ongoing-Study/cpp/subprocess_output/subprocess_output-winapi.c
// Boost.process
// [How to detect "Use MFC" in preprocessor](https://stackoverflow.com/questions/1196808/how-to-detect-use-mfc-in-preprocessor)
// clang-format on
