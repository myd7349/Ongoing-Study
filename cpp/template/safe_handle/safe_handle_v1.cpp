#include <cstdint>
#include <cstdio>
#include <functional>

template <typename T>
class Handle {
 public:
  Handle(std::function<void(T)> close)
      : close_(close) {}

 private:
  std::function<void(T)> close_;
};

typedef void *HANDLE;

void CloseHandle() {
}


template <std::intptr_t INVALID_HANDLE>
class Win32Handle : public Handle<HANDLE> {
 public:
  Win32Handle(std::intptr_t handle) : Handle([](HANDLE) {}) {}
};

int main() {
  Win32Handle<NULL> h(1);
  return 0;
}
