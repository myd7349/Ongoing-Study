#include <cstdint>

#include <fmt/core.h>

int main() {
  std::int32_t a = -42;
  fmt::print("The answer is {:032b}\n.", static_cast<std::uint32_t>(a));
  fmt::print("The answer is {:064b}\n.", static_cast<std::uint64_t>(a));
}


// References:
// https://fmt.dev/latest/index.html
// https://fmt.dev/latest/syntax.html
// https://www.reddit.com/r/cpp/comments/81ta6q/the_fmt_formatting_library_is_now_available_in/
// [Sign extend a nine-bit number in C](https://stackoverflow.com/questions/5814072/sign-extend-a-nine-bit-number-in-c)
// https://graphics.stanford.edu/~seander/bithacks.html#FixedSignExtend
// http://www.c-jump.com/CIS77/CPU/Numbers/U77_0160_sign_extension.htm
// [Bit Padding (C)](https://stackoverflow.com/questions/42910368/bit-padding-c)
