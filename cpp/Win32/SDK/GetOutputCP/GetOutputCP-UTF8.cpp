#include <iostream>

#include <windows.h>

int main() {
  UINT cp = GetConsoleOutputCP();
#ifdef SET_CP_UTF8
  SetConsoleOutputCP(CP_UTF8);
#endif
  std::cout << u8"代码页：" << cp << std::endl;
#ifdef SET_CP_UTF8
  SetConsoleOutputCP(cp);
#endif
  return 0;
}

// References:
// [Change Console Code Page in Windows C++](https://stackoverflow.com/questions/23471873/change-console-code-page-in-windows-c)
