#include <stdio.h>

#include <windows.h>

int main(void) {
  printf("%u", GetConsoleOutputCP());
  return 0;
}

// References:
// [Change Console Code Page in Windows C++](https://stackoverflow.com/questions/23471873/change-console-code-page-in-windows-c)
