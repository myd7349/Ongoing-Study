#pragma once

template <typename T, T INVALID_HANDLE>
class Handle {
 public:
  Handle(T handle, std::function<void(T)> close)
      : handle_(handle), close_(close) {}

  Handle(std::function<void(T)> close) : Handle(INVALID_HANDLE, close) {}

  ~Handle() { Close(); }

  operator T() const { return handle_; }

  bool operator!() const { return handle_ == INVALID_HANDLE; }

  void Attach(T handle) {
    if (handle != handle_) {
      Close();
      handle_ = handle;
    }
  }

  T Detach() {
    T oldHandle = handle_;
    handle_ = INVALID_HANDLE;
    return oldHandle;
  }

  void Close() {
    if (handle_ != INVALID_HANDLE) {
      close_(handle_);
      handle_ = INVALID_HANDLE;
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
__declspec(dllimport) int __stdcall CloseHandle(void *);

template <HANDLE INVALID_HANDLE>
class Win32Handle : public Handle<void *, INVALID_HANDLE> {
 public:
  Win32Handle(void *handle = INVALID_HANDLE)
      : Handle(handle, [](HANDLE h) { CloseHandle(h); }) {}
};
#endif

// clang-format off
// References:
// https://github.com/eidheim/tiny-process-library/blob/master/process_win.cpp
// [C++ assignment operator in derived class](https://stackoverflow.com/questions/31029007/c-assignment-operator-in-derived-class)
// clang-format on
