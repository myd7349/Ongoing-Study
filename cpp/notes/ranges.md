[std::ranges::views::iota, std::ranges::iota_view - cppreference.com](https://en.cppreference.com/w/cpp/ranges/iota_view)

```cpp
#include <ranges>
#include <fmt/core.h>

int main() {
  for (auto x : std::views::iota(1, 10)) {
    fmt::print("{}\n", x);
  }
}
```


