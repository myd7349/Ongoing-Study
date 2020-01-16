#include <iostream>
#include <sstream>

#include "Error.h"
#include "Subprocess.h"

void ReportError(const string_type &hint) {
  std::cerr << hint << " failed with " << GetLastError() << ": "
            << TranslateError() << '\n';
}

class OutputCapturer {
 public:
  void Clear() { oss_.clear(); }

  string_type GetOutput() const { return oss_.str(); }

  void operator()(LPVOID buffer, DWORD dwBytes) {
    oss_.rdbuf()->sputn(static_cast<const char *>(buffer), dwBytes);
  }

 private:
  std::ostringstream oss_;
};

void ProcessOutput(LPVOID bytes, DWORD dwBytes) {
  std::cout.rdbuf()->sputn(static_cast<const char *>(bytes), dwBytes);
  std::cout << std::flush;
}

int main() {
  {
    Subprocess process({"cmd", "/c", "dir", "/s", "/b"}, ProcessOutput);
    DWORD dwExitCode;
    if (process.Wait(dwExitCode)) {
      std::cout << "Exit code: " << dwExitCode << std::endl;
    } else {
      std::cerr << "Failed to launch process.\n";
    }
  }
  {
    Subprocess process("cmd", {"/c", "dir", "/s", "/b"}, ProcessOutput);
    DWORD dwExitCode;
    if (process.Wait(dwExitCode)) {
      std::cout << "Exit code: " << dwExitCode << std::endl;
    } else {
      ReportError(process.GetLastErrorHint());
    }
  }
  { Subprocess process("cmd /c ver", ProcessOutput); }

  return 0;
}

// clang-format off
// References:
// [Passing a non-copyable closure object to std::function parameter](https://stackoverflow.com/questions/20843271/passing-a-non-copyable-closure-object-to-stdfunction-parameter)
// clang-format on
