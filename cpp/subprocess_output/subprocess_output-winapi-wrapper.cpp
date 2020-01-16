#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

#include "Error.h"
#include "Subprocess.h"

void ReportError(const string_type &hint) {
  std::cerr << hint << " failed with " << GetLastError() << ": "
            << TranslateError() << '\n';
}

#if 0
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
#else
class OutputCapturer {
 public:
  void Clear() { data_.clear(); }

  string_type GetOutput() const {
    std::vector<unsigned char> data(data_);
    data.push_back('\0');
    data.push_back('\0');

    return reinterpret_cast<LPCTSTR>(data.data());
  }

  void operator()(LPVOID buffer, DWORD dwBytes) {
    assert(buffer != nullptr && dwBytes > 0);

    std::copy(static_cast<const unsigned char *>(buffer),
              static_cast<const unsigned char *>(buffer) + dwBytes,
              std::back_inserter(data_));
  }

 private:
  std::vector<unsigned char> data_;
};
#endif

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
  {
    OutputCapturer capturer;
    Subprocess process("cmd /c ver", std::ref(capturer));
    DWORD dwExitCode;
    if (process.Wait(dwExitCode)) {
      std::cout << "Exit code: " << dwExitCode << std::endl;
      std::cout << "Output: " << capturer.GetOutput() << std::endl;
    }
  }

  return 0;
}

// clang-format off
// References:
// [Passing a non-copyable closure object to std::function parameter](https://stackoverflow.com/questions/20843271/passing-a-non-copyable-closure-object-to-stdfunction-parameter)
// clang-format on
