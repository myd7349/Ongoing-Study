#include <errno.h>
#include <stdio.h>
#include <tchar.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
int main() {
  FILE *fpipe = _tpopen(_T("cmd /c dir /s /b"), _T("rt"));
  if (fpipe == NULL) {
    _ftprintf(stderr, _T("popen failed(%d): %s.\n"), errno, _tcserror(errno));
    return 1;
  }

  _TCHAR buffer[512] = _T("");
  while (_fgetts(buffer, ARRAY_SIZE(buffer), fpipe) != NULL)
    fprintf(stdout, "%s", buffer);

  if (feof(fpipe)) {
    _ftprintf(stdout, _T("Done!\n"));
  } else if (ferror(fpipe)) {
    _ftprintf(stderr, _T("error(%d): %s.\n"), errno, _tcserror(errno));
  } else {
  }

  int exit_code = _pclose(fpipe);
  _ftprintf(stdout, "Exit code: %d\n", exit_code);

  return 0;
}

// References:
// https://github.com/myd7349/mydstudy/blob/master/del_types.zip
// [Creating a Child Process with Redirected Input and Output](https://docs.microsoft.com/en-us/windows/win32/procthread/creating-a-child-process-with-redirected-input-and-output)
// [Using a handle to collect output from CreateProcess()](https://stackoverflow.com/questions/2674237/using-a-handle-to-collect-output-from-createprocess)
// [launch an exe/process with stdin stdout and stderr?](https://stackoverflow.com/questions/5485923/launch-an-exe-process-with-stdin-stdout-and-stderr/39648986)
// [c++: subprocess output to stdin](https://stackoverflow.com/questions/8438277/c-subprocess-output-to-stdin)
