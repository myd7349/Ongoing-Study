#pragma once

#include <cstdint>
#include <functional>


template <typename T, std::intptr_t INVALID_HANDLE>
class Handle {
 public:
  Handle(T handle, std::function<void(T)> close)
      : handle_(handle), close_(close) {}

  Handle(std::function<void(T)> close) : Handle(reinterpret_cast<T>(INVALID_HANDLE), close) {}

  virtual ~Handle() { Close(); }

  operator T() const { return handle_; }

  bool operator!() const { return handle_ == reinterpret_cast<T>(INVALID_HANDLE); }

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
  Win32Handle(HANDLE handle)
      : Handle(handle, [](HANDLE h) { CloseHandle(h); }) {}
#elif 0
  Win32Handle(HANDLE handle)
      : Handle(handle, [](HANDLE h) { CloseHandle(h); }) {}
  Win32Handle(std::intptr_t handle = INVALID_HANDLE)
      : Win32Handle(reinterpret_cast<HANDLE>(handle)) {}
#else
  Win32Handle(std::intptr_t handle = INVALID_HANDLE)
      : Handle(reinterpret_cast<HANDLE>(handle), [](HANDLE h) { CloseHandle(h); }) {}
#endif
};
#endif

// clang-format off
// References:
// https://github.com/eidheim/tiny-process-library/blob/master/process_win.cpp
// [C++ assignment operator in derived class](https://stackoverflow.com/questions/31029007/c-assignment-operator-in-derived-class)
// [unique_ptr 的小技巧：包装 Win32 的 file handle](https://zhuanlan.zhihu.com/p/24176727)
/*
struct FileHandle
{
    ::HANDLE fileHandle;

    //implicit
    FileHandle(::HANDLE h) noexcept
        : fileHandle{h}
    {}

    //implicit
    FileHandle(std::nullptr_t = nullptr) noexcept
        : FileHandle{ INVALID_HANDLE_VALUE }
    {}

    operator ::HANDLE() noexcept { return fileHandle; }

    explicit operator bool() noexcept { return fileHandle != INVALID_HANDLE_VALUE; }
};

bool operator== (FileHandle lhs, FileHandle rhs) noexcept
{
    return lhs.fileHandle == rhs.fileHandle;
}

bool operator!= (FileHandle lhs, FileHandle rhs) noexcept
{
    return !(lhs == rhs);
}

struct FileCloser
{
    using pointer = FileHandle;

    void operator()(pointer p) const noexcept
    {
        (void)::CloseHandle(p.fileHandle);
    }
};

using UniqueFile = std::unique_ptr<void, FileCloser>;
*/
// [Uses of pointers non-type template parameters?](https://stackoverflow.com/questions/13220502/uses-of-pointers-non-type-template-parameters)
// https://chromium.googlesource.com/chromium/src/+/refs/heads/main/base/win/scoped_handle.h
// [Can a non-type template parameter be of type "void*"?](https://stackoverflow.com/questions/56003162/can-a-non-type-template-parameter-be-of-type-void)
// clang-format on
