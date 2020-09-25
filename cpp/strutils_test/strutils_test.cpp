// clang-format off
#include <iostream>

#include "../strutils.hpp"
// clang-format on


int main() {
  std::wcout.imbue(std::locale(""));

  std::wstring tips_cn = L"    请联系作者~    ";
  std::wcout << L'<' << Trim(tips_cn) << L'>' << std::endl;
  return 0;
}
