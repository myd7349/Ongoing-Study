#include <stdio.h>

#define MY_MACRO "Hello, "

void print_macro_0(void) { puts(MY_MACRO); }

#pragma push_macro("MY_MACRO")
#undef MY_MACRO
#define MY_MACRO "world!"

void print_macro_1(void) { puts(MY_MACRO); }

#pragma pop_macro("MY_MACRO")

void print_macro_2(void) { puts(MY_MACRO); }

int main(void) {
  print_macro_0();
  print_macro_1();
  print_macro_2();
  return 0;
}

// References:
// https://github.com/Tencent/rapidjson/pull/1877
