#include <iostream>

#include <windows.h>

int main() {
  std::cout << "´úÂëÒ³£º" << GetConsoleOutputCP() << std::endl;
  return 0;
}

// References:
// [Change Console Code Page in Windows C++](https://stackoverflow.com/questions/23471873/change-console-code-page-in-windows-c)
