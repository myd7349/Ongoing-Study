#include <cstdint>
#include <functional>

template <typename T, std::intptr_t INVALID_HANDLE>
class Handle {
 public:
  Handle(T handle, std::function<void(T)> close)
      : handle_(handle), close_(close) {}

  Handle(std::function<void(T)> close)
      : Handle(reinterpret_cast<T>(INVALID_HANDLE), close) {}

  virtual ~Handle() { Close(); }

  operator T() const { return handle_; }

  bool operator!() const {
    return handle_ == reinterpret_cast<T>(INVALID_HANDLE);
  }

  void Attach(T handle) {
    if (handle != handle_) {
      Close();
      handle_ = handle;
    }
  }

  T Detach() {
    T oldHandle = handle_;
    handle_ = reinterpret_cast<T>(INVALID_HANDLE);
    return oldHandle;
  }

  void Close() {
    if (handle_ != reinterpret_cast<T>(INVALID_HANDLE)) {
      close_(handle_);
      handle_ = reinterpret_cast<T>(INVALID_HANDLE);
    }
  }

  T *operator&() noexcept { return &handle_; }

 private:
  Handle(const Handle &) = delete;
  Handle &operator=(const Handle &) = delete;

  T handle_;
  std::function<void(T)> close_;
};

#ifdef _WIN32
#include <Windows.h>

// TODO:
// Win32Handle<INVALID_HANDLE_VALUE> will not work.
// Since INVALID_HANDLE_VALUE might be defined as:
// #define INVALID_HANDLE_VALUE ((HANDLE)(LONG_PTR)-1)
template <std::intptr_t INVALID_HANDLE>
class Win32Handle : public Handle<HANDLE, INVALID_HANDLE> {
 public:
#if 0
  Win32Handle(HANDLE handle = INVALID_HANDLE)
      : Handle(handle, [](HANDLE h) { CloseHandle(h); }) {}
#elif 0
  Win32Handle(HANDLE handle)
      : Handle(handle, [](HANDLE h) { CloseHandle(h); }) {}
  Win32Handle(std::intptr_t handle = INVALID_HANDLE)
      : Win32Handle(reinterpret_cast<HANDLE>(handle)) {}
#else
  Win32Handle(std::intptr_t handle = INVALID_HANDLE)
      : Handle(reinterpret_cast<HANDLE>(handle),
               [](HANDLE h) { CloseHandle(h); }) {}
#endif
};
#endif

class A {
 public:
    A()
    {
    }
  Win32Handle<NULL> h;
};

int main() {
  A a;
  return 0;
}
