// clang-format off
#include <stdio.h>
#include <string.h>

#include <tchar.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <strsafe.h>
// clang-format on

#define BUFSIZE 4096

void ErrorExit(PTSTR lpszFunction) {
  LPVOID lpMsgBuf;
  LPVOID lpDisplayBuf;
  DWORD dw = GetLastError();

  FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
                    FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL, dw, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                (LPTSTR)&lpMsgBuf, 0, NULL);

  lpDisplayBuf = (LPVOID)LocalAlloc(
      LMEM_ZEROINIT,
      (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) *
          sizeof(TCHAR));
  StringCchPrintf((LPTSTR)lpDisplayBuf, LocalSize(lpDisplayBuf) / sizeof(TCHAR),
                  TEXT("%s failed with error %d: %s"), lpszFunction, dw,
                  lpMsgBuf);
  MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK | MB_ICONERROR);

  LocalFree(lpMsgBuf);
  LocalFree(lpDisplayBuf);
  ExitProcess(1);
}

// Create a child process that uses the previously created pipes for STDIN and
// STDOUT.
HANDLE CreateChildProcess(LPCTSTR lpcszCommandline,
                          HANDLE hChildStdOutWritePipe,
                          HANDLE hChildStdInReadPipe) {
  size_t length = _tcslen(lpcszCommandline);
  if (length >= BUFSIZE) ErrorExit(_T("This command is too long!"));

  TCHAR szCmdline[BUFSIZE];
  _tcsncpy(szCmdline, lpcszCommandline, BUFSIZE);

  PROCESS_INFORMATION piProcInfo;
  STARTUPINFO siStartInfo;
  BOOL bSuccess = FALSE;

  // Set up members of the PROCESS_INFORMATION structure.
  ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));

  // Set up members of the STARTUPINFO structure.
  // This structure specifies the STDIN and STDOUT handles for redirection.

  ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
  siStartInfo.cb = sizeof(STARTUPINFO);
  siStartInfo.hStdError = hChildStdOutWritePipe;
  siStartInfo.hStdOutput = hChildStdOutWritePipe;
  siStartInfo.hStdInput = INVALID_HANDLE_VALUE;
  // siStartInfo.wShowWindow = SW_HIDE;
  siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

  // Create the child process.
  bSuccess = CreateProcess(NULL,
                           szCmdline,  // command line
                           NULL,       // process security attributes
                           NULL,       // primary thread security attributes
                           TRUE,       // handles are inherited
                           CREATE_NO_WINDOW,  // creation flags
                           NULL,              // use parent's environment
                           NULL,              // use parent's current directory
                           &siStartInfo,      // STARTUPINFO pointer
                           &piProcInfo);      // receives PROCESS_INFORMATION

  // If an error occurs, exit the application.
  if (!bSuccess) ErrorExit(TEXT("CreateProcess"));

  // Close handles to the child process and its primary thread.
  // Some applications might keep these handles to monitor the status
  // of the child process, for example.
  CloseHandle(piProcInfo.hThread);

  return piProcInfo.hProcess;
}

// Read output from the child process's pipe for STDOUT
// and write to the parent process's pipe for STDOUT.
// Stop when there is no more data.
void ReadFromPipe(HANDLE hChildStdOutReadPipe) {
  DWORD dwRead, dwWritten;
  CHAR chBuf[BUFSIZE];
  BOOL bSuccess = FALSE;
  HANDLE hParentStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

  while (TRUE) {
    bSuccess = ReadFile(hChildStdOutReadPipe, chBuf, BUFSIZE, &dwRead, NULL);
    if (!bSuccess || dwRead == 0) break;

    bSuccess = WriteFile(hParentStdOut, chBuf, dwRead, &dwWritten, NULL);
    if (!bSuccess) break;
  }
}

BOOL RunCommand(LPCTSTR lpcszCommand) {
  SECURITY_ATTRIBUTES sa;

  ZeroMemory(&sa, sizeof(sa));
  // Set the bInheritHandle flag so pipe handles are inherited.
  sa.nLength = sizeof(SECURITY_ATTRIBUTES);
  sa.bInheritHandle = TRUE;
  sa.lpSecurityDescriptor = NULL;

  HANDLE hChildStdOutReadPipe;
  HANDLE hChildStdOutWritePipe;

  // Create a pipe for the child process's STDOUT.
  if (!CreatePipe(&hChildStdOutReadPipe, &hChildStdOutWritePipe, &sa, 0))
    ErrorExit(TEXT("CreatePipe failed."));

  // Ensure the read handle to the pipe for STDOUT is not inherited.
  if (!SetHandleInformation(hChildStdOutReadPipe, HANDLE_FLAG_INHERIT, 0))
    ErrorExit(TEXT("Stdout SetHandleInformation"));

  HANDLE hChildStdInReadPipe;
  HANDLE hChildStdInWritePipe;

  // Create a pipe for the child process's STDIN.
  if (!CreatePipe(&hChildStdInReadPipe, &hChildStdInWritePipe, &sa, 0))
    ErrorExit(TEXT("Stdin CreatePipe"));

  // Ensure the write handle to the pipe for STDIN is not inherited.
  if (!SetHandleInformation(hChildStdInWritePipe, HANDLE_FLAG_INHERIT, 0))
    ErrorExit(TEXT("Stdin SetHandleInformation"));

  HANDLE hChildProcess = CreateChildProcess(lpcszCommand, hChildStdOutWritePipe,
                                            hChildStdInReadPipe);

#if 0
  // Write to child process' STDIN.
  DWORD dwBytesToWrite = (_tcslen(szCommand) + 1) * sizeof(_TCHAR);
  DWORD dwBytesWritten;
  LPBYTE lpbyBuffer = (LPBYTE)szCommand;

  while (dwBytesToWrite > 0) {
    if (!WriteFile(hChildStdInWritePipe, lpbyBuffer, dwBytesToWrite,
                   &dwBytesWritten, NULL)) {
      _ftprintf(stderr, _T("Failed to write to child process's STDIN pipe.\n"));
      break;
    }

    dwBytesToWrite -= dwBytesWritten;
    lpbyBuffer += dwBytesWritten;
  }
#endif

  // Close the pipe handle so the child process stops reading.
  if (!CloseHandle(hChildStdInWritePipe))
    ErrorExit(TEXT("StdInWr CloseHandle"));

  DWORD dwExitCode;
  switch (WaitForSingleObject(hChildProcess, INFINITE)) {
    case WAIT_TIMEOUT:
      break;
    case WAIT_FAILED:
      break;
    case WAIT_OBJECT_0:
      if (GetExitCodeProcess(hChildProcess, &dwExitCode))
        _ftprintf(stdout, "Exit code: %d\n", (int)dwExitCode);
      CloseHandle(hChildProcess);
      CloseHandle(hChildStdOutWritePipe);  // Close it, otherwise ReadFromPipe
                                           // will hang with `ReadFile`.
      break;
    default:
      break;
  }

  ReadFromPipe(hChildStdOutReadPipe);

  return TRUE;
}

BOOL RunFromInput() {
  TCHAR szCommand[MAX_PATH];
  if (_fgetts(szCommand, ARRAYSIZE(szCommand), stdin) != NULL) {
    TCHAR *lpLF = _tcschr(szCommand, _T('\n'));
    if (lpLF != NULL) {
      *lpLF = _T('\0');
    } else {
      return FALSE;
    }
    if (_tcscmp(szCommand, "q") == 0 || _tcscmp(szCommand, "Q") == 0)
      return FALSE;
  } else {
    return FALSE;
  }

  return RunCommand(szCommand);
}

int main(void) {
  RunCommand(_T("cmd /c ver"));
  while (RunFromInput()) {
  }

  return 0;
}

// clang-format off
// References:
// [Creating a Child Process with Redirected Input and Output](https://docs.microsoft.com/en-us/windows/win32/procthread/creating-a-child-process-with-redirected-input-and-output)
// [Using a handle to collect output from CreateProcess()](https://stackoverflow.com/questions/2674237/using-a-handle-to-collect-output-from-createprocess)
// [launch an exe/process with stdin stdout and stderr?](https://stackoverflow.com/questions/5485923/launch-an-exe-process-with-stdin-stdout-and-stderr/39648986)
// [c++: subprocess output to stdin](https://stackoverflow.com/questions/8438277/c-subprocess-output-to-stdin)
// https://github.com/pbatard/libwdi/blob/master/libwdi/logging.c
// https://github.com/eidheim/tiny-process-library/blob/master/process_win.cpp
// https://github.com/tsaarni/cpp-subprocess
// C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\crt\src\popen.c
// C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\crt\src\pipe.c
// C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\crt\src\osfinfo.c
// [capture process stdout and stderr in the correct ordering](https://stackoverflow.com/questions/18529662/capture-process-stdout-and-stderr-in-the-correct-ordering)
// [Preserve output order when redirecting stdout and stderr](https://www.unix.com/shell-programming-and-scripting/126488-preserve-output-order-when-redirecting-stdout-stderr.html)
// [Win32 ReadFile hangs when reading from pipe](https://stackoverflow.com/questions/13816962/win32-readfile-hangs-when-reading-from-pipe)
// clang-format on
