// clang-format off
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <process.h>
#include <tchar.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <strsafe.h>
// clang-format on

#define BUFSIZE 4096

void ReportError(LPTSTR lpszFunction) {
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
  _ftprintf(stderr, _T("%s"), (LPTSTR)lpDisplayBuf);

  LocalFree(lpMsgBuf);
  LocalFree(lpDisplayBuf);
}

// Create a child process that uses the previously created pipes for STDIN and
// STDOUT.
HANDLE CreateChildProcess(LPCTSTR lpcszCommandline,
                          HANDLE hChildStdOutWritePipe) {
  size_t length = _tcslen(lpcszCommandline);
  if (length >= BUFSIZE) {
    ReportError(_T("This command is too long!"));
    return NULL;
  }

  TCHAR szCmdline[BUFSIZE];
  _tcsncpy(szCmdline, lpcszCommandline, BUFSIZE);

  PROCESS_INFORMATION piProcInfo;
  STARTUPINFO siStartInfo;
  BOOL bSuccess = FALSE;

  // Set up members of the PROCESS_INFORMATION structure.
  ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));

  // Set up members of the STARTUPINFO structure.
  // This structure specifies STDOUT and STDERR handles for redirection.

  ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
  siStartInfo.cb = sizeof(STARTUPINFO);
  siStartInfo.hStdError = hChildStdOutWritePipe;
  siStartInfo.hStdOutput = hChildStdOutWritePipe;
  siStartInfo.hStdInput = NULL;
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
  if (!bSuccess) {
    ReportError(TEXT("CreateProcess"));
    return NULL;
  }

  // Close handles to the child process and its primary thread.
  // Some applications might keep these handles to monitor the status
  // of the child process, for example.
  CloseHandle(piProcInfo.hThread);

  return piProcInfo.hProcess;
}

// Read output from the child process's pipe for STDOUT
// and write to the parent process's pipe for STDOUT.
// Stop when there is no more data.
unsigned int __stdcall ReadFromPipe(void *arg) {
  HANDLE hChildStdOutReadPipe = (HANDLE)arg;

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

  return 0;
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
  if (!CreatePipe(&hChildStdOutReadPipe, &hChildStdOutWritePipe, &sa, 0)) {
    ReportError(TEXT("CreatePipe"));
    return FALSE;
  }

  // Ensure the read handle to the pipe for STDOUT is not inherited.
  if (!SetHandleInformation(hChildStdOutReadPipe, HANDLE_FLAG_INHERIT, 0)) {
    ReportError(TEXT("SetHandleInformation"));
    return FALSE;
  }

  HANDLE hChildProcess =
      CreateChildProcess(lpcszCommand, hChildStdOutWritePipe);
  if (hChildProcess == NULL) {
    CloseHandle(hChildStdOutReadPipe);
    CloseHandle(hChildStdOutWritePipe);
    return FALSE;
  }

  HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, ReadFromPipe,
                                          hChildStdOutReadPipe, 0, NULL);
  if (hThread == NULL) ReportError(TEXT("_beginthreadex"));

  DWORD dwExitCode;
  switch (WaitForSingleObject(hChildProcess, INFINITE)) {
    case WAIT_TIMEOUT:
      assert(FALSE);
      break;
    case WAIT_FAILED:
      ReportError(_T("WaitForSingleObject"));
      break;
    case WAIT_OBJECT_0:
      if (GetExitCodeProcess(hChildProcess, &dwExitCode))
        _ftprintf(stdout, "Exit code: %d\n", (int)dwExitCode);
      CloseHandle(hChildProcess);
      CloseHandle(hChildStdOutWritePipe);  // Close it, otherwise ReadFromPipe
                                           // will hang with `ReadFile`.
      break;
    default:
      assert(FALSE);
      break;
  }

  if (hThread != NULL) {
    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);
  }

  CloseHandle(hChildStdOutReadPipe);

  return TRUE;
}

int main(void) {
  RunCommand(_T("cmd /c ver"));
  // RunCommand(_T("cmd /c dir /s /b C:\\"));
  RunCommand(_T("cmd /c dir /s /b ."));

  TCHAR szCommand[MAX_PATH];

  while (_fgetts(szCommand, ARRAYSIZE(szCommand), stdin) != NULL) {
    TCHAR *lpLF = _tcschr(szCommand, _T('\n'));
    if (lpLF != NULL) {
      *lpLF = _T('\0');
    } else {
      _ftprintf(stderr, _T("This command is too long!\n"));
      continue;
    }

    if (szCommand[0] == _T('\0')) continue;
    if (_tcscmp(szCommand, "q") == 0 || _tcscmp(szCommand, "Q") == 0) break;

    RunCommand(szCommand);
  }

  return 0;
}

// clang-format off
// References:
// [Creating a Child Process with Redirected Input and Output](https://docs.microsoft.com/en-us/windows/win32/procthread/creating-a-child-process-with-redirected-input-and-output)
// https://github.com/MicrosoftDocs/win32/blob/docs/desktop-src/ProcThread/creating-a-child-process-with-redirected-input-and-output.md
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
// [How to get Windows version from command prompt or from PowerShell](https://stackoverflow.com/questions/42778858/how-to-get-windows-version-from-command-prompt-or-from-powershell)
// [Find windows OS version from command line](https://www.windows-commandline.com/find-windows-os-version-from-command/)
// clang-format on
