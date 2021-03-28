#pragma once

#include <chrono>

class high_timer {
 public:
  high_timer() { start(); }

  inline void start() { start_ = std::chrono::high_resolution_clock::now(); }

  inline std::chrono::milliseconds::rep get_elapsed_ms() const {
    // using namespace std::literals;
    using namespace std::chrono_literals;
    auto end = std::chrono::high_resolution_clock::now();
    // return std::chrono::duration_cast<std::chrono::milliseconds>(end -
    // start_).count();
    return (end - start_) / 1ms;
  }

  inline std::chrono::microseconds::rep get_elapsed_us() const {
    using namespace std::chrono_literals;
    auto end = std::chrono::high_resolution_clock::now();
    return (end - start_) / 1us;
  }

  inline std::chrono::nanoseconds::rep get_elapsed_ns() const {
    using namespace std::chrono_literals;
    auto end = std::chrono::high_resolution_clock::now();
    return (end - start_) / 1ns;
  }

 private:
  std::chrono::high_resolution_clock::time_point start_;
};

// References:
// https://github.com/mattreecebentley/plf_nanotimer
// https://github.com/wichtounet/articles/blob/master/include/bench.hpp
// https://en.cppreference.com/w/cpp/chrono/time_point
// https://en.cppreference.com/w/cpp/thread/sleep_for
