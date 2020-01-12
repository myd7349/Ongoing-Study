#include <iostream>

#include <process.hpp>


void ProcessOutput(const char *bytes, std::size_t n) {
  std::cout.rdbuf()->sputn(bytes, n);
}

int main() {
  const char *command_line =
      "cmd /c"
      " \""
      " \"ReportGenerator.exe\""
      " -i \"ReportTemplate.frx\""
      " -o \"Output.png\""
      " -f Png"
      "\""
      " & exit ^!errorlevel^!";

  TinyProcessLib::Process process(command_line, ".", ProcessOutput,
                                  ProcessOutput);
  auto exit_code = process.get_exit_status();
  std::cout << "Exit code: " << exit_code << std::endl;

  return 0;
}

// References:
// [Creating a Child Process with Redirected Input and Output](https://docs.microsoft.com/en-us/windows/win32/procthread/creating-a-child-process-with-redirected-input-and-output)
// [Using a handle to collect output from CreateProcess()](https://stackoverflow.com/questions/2674237/using-a-handle-to-collect-output-from-createprocess)
// [launch an exe/process with stdin stdout and stderr?](https://stackoverflow.com/questions/5485923/launch-an-exe-process-with-stdin-stdout-and-stderr/39648986)
// [c++: subprocess output to stdin](https://stackoverflow.com/questions/8438277/c-subprocess-output-to-stdin)
