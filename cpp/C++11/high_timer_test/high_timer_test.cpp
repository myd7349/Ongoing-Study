#include <chrono>
#include <iostream>
#include <thread>

#include "high_timer.hpp"

int main() {
  using namespace std::chrono_literals;

  high_timer timer;
  std::this_thread::sleep_for(1000ms);
  std::cout << timer.get_elapsed_ms() << std::endl;
  std::cout << timer.get_elapsed_us() << std::endl;
  std::cout << timer.get_elapsed_ns() << std::endl;
  return 0;
}
