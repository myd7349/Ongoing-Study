#include <iostream>

int main() {
  std::cout << "cout at line " << __LINE__ << std::endl;
  std::cerr << "cerr at line " << __LINE__ << std::endl;
  std::cout << "cout at line " << __LINE__ << std::endl;
  std::cerr << "cerr at line " << __LINE__ << std::endl;

  return 0;
}

// References:
// [capture process stdout and stderr in the correct ordering](https://stackoverflow.com/questions/18529662/capture-process-stdout-and-stderr-in-the-correct-ordering)
// [Preserve output order when redirecting stdout and stderr](https://www.unix.com/shell-programming-and-scripting/126488-preserve-output-order-when-redirecting-stdout-stderr.html)
