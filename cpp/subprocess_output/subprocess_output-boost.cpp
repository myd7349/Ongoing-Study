#include <iostream>
#include <string>

#include <boost/process.hpp>

int main() {
  const char *command_line = "cmd /c dir /s /b";

  boost::process::ipstream pipe_stream;
  boost::process::child subprocess(command_line, boost::process::std_out > pipe_stream);

  std::string line;
  while (pipe_stream && std::getline(pipe_stream, line))
      std::cout << line << std::endl;

  subprocess.wait();

  return 0;
}

// clang-format off
// References:
// https://www.boost.org/doc/libs/1_72_0/doc/html/process.html
// clang-format on
