#include <iostream>
#include <mutex>

#include <process.hpp>

std::mutex output_mutex;

void ProcessOutput(const char *bytes, std::size_t n) {
  std::lock_guard<std::mutex> lock(output_mutex);
  std::cout.rdbuf()->sputn(bytes, n);
  std::cout << std::flush;
}

void ProcessStderr(const char *bytes, std::size_t n) {
  std::lock_guard<std::mutex> lock(output_mutex);
  std::cout.rdbuf()->sputn(bytes, n);
  std::cout << std::flush;
}

int main() {
  const char *command_line = "cmd /c dir /s /b";

  TinyProcessLib::Process process(command_line, ".", ProcessOutput,
                                  ProcessOutput);
  auto exit_code = process.get_exit_status();
  std::cout << "Exit code: " << exit_code << std::endl;

  // What is the output of following code?
  TinyProcessLib::Process process2("stdout_stderr_order", "", ProcessOutput,
                                   ProcessStderr);
  exit_code = process2.get_exit_status();
  std::cout << "Exit code: " << exit_code << std::endl;

  return 0;
}

// clang-format off
// References:
// [Creating a Child Process with Redirected Input and Output](https://docs.microsoft.com/en-us/windows/win32/procthread/creating-a-child-process-with-redirected-input-and-output)
// [Using a handle to collect output from CreateProcess()](https://stackoverflow.com/questions/2674237/using-a-handle-to-collect-output-from-createprocess)
// [launch an exe/process with stdin stdout and stderr?](https://stackoverflow.com/questions/5485923/launch-an-exe-process-with-stdin-stdout-and-stderr/39648986)
// [c++: subprocess output to stdin](https://stackoverflow.com/questions/8438277/c-subprocess-output-to-stdin)
// https://stackoverflow.com/questions/45486602/blocking-until-process-ends-in-tiny-process-library
// [capture process stdout and stderr in the correct ordering](https://stackoverflow.com/questions/18529662/capture-process-stdout-and-stderr-in-the-correct-ordering)
// [Preserve output order when redirecting stdout and stderr](https://www.unix.com/shell-programming-and-scripting/126488-preserve-output-order-when-redirecting-stdout-stderr.html)
// https://gitlab.com/eidheim/tiny-process-library/issues/41
// clang-format on
