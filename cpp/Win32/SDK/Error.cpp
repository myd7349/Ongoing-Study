#include "Error.h"

std::basic_string<TCHAR> TranslateError(DWORD dwErrorCode, DWORD dwLangID) {
  LPVOID lpMsgBuf;

  FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
                    FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL, dwErrorCode, dwLangID, (LPTSTR)&lpMsgBuf, 0, NULL);

  std::basic_string<TCHAR> errorMessage = (LPTSTR)lpMsgBuf;
  LocalFree(lpMsgBuf);

  return errorMessage;
}

// clang-format off
// References:
// https://github.com/MicrosoftDocs/win32/blob/docs/desktop-src/ProcThread/creating-a-child-process-with-redirected-input-and-output.md
// clang-format on
