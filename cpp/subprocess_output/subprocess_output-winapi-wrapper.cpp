#include <iostream>
#include <sstream>

#include "Subprocess.h"

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
    Subprocess process(nullptr, "reportgenerator --help", ProcessOutput, FALSE);
  }
  { Subprocess process("cmd /c ver", ProcessOutput); }

  return 0;
}

// References:
// [Passing a non-copyable closure object to std::function
// parameter](https://stackoverflow.com/questions/20843271/passing-a-non-copyable-closure-object-to-stdfunction-parameter)
