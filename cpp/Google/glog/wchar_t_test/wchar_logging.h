#ifndef WCHAR_LOGGING_H_
#define WCHAR_LOGGING_H_

#include <cwchar>
#include <iostream>
#include <string>


inline std::ostream& operator<<(std::ostream& out, const wchar_t* str) {
  std::mbstate_t state = std::mbstate_t();
  std::size_t len = std::wcsrtombs(nullptr, &str, 0, &state);
  if (len != static_cast<std::size_t>(-1)) {
    char* buf = new char[len + 1];
    buf[len] = 0;
    std::wcsrtombs(buf, &str, len + 1, &state);
    out << buf;
    delete[] buf;
  } else {
    out << "<Internal error> Failed to convert wide string to mbs one.";
  }

  return out;
}

inline std::ostream& operator<<(std::ostream& out, const std::wstring& str) {
  return operator<<(out, str.c_str());
}

#endif  // WCHAR_LOGGING_H_


// References:
// https://github.com/baysao/google-glog/issues/4
