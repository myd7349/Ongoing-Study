#include <algorithm>
#include <deque>
#include <functional>
#include <iostream>
#include <iterator>

int main() {
  auto print_deq = [](std::ostream &os, const std::deque<int> &deq) {
    os << '[';

    if (!deq.empty()) {
      std::copy(deq.cbegin(), deq.cend() - 1,
                std::ostream_iterator<int>(os, ", "));
      os << deq.back();
    }

    os << "]\n";
  };

  auto cout_deq =
      std::bind(print_deq, std::ref(std::cout), std::placeholders::_1);

  int nums[] = {10, 8, 6, 4, 2, 0};

  {
    std::deque<int> sequence{1, 3, 5, 7, 9};

    for (int n : nums)
      sequence.insert(std::upper_bound(sequence.cbegin(), sequence.cend(), n),
                      n);

    cout_deq(sequence);
  }

  {
    std::deque<int> sequence{1, 3, 5, 7, 9};

    for (int n : nums)
      sequence.insert(
          std::upper_bound(sequence.cbegin(), sequence.cend(), n,
                           [](int value, int x) { return value < x; }),
          n);

    cout_deq(sequence);
  }

  std::cin.get();

  return 0;
}

// References:
// [how do you insert the value in a sorted
// vector?](https://stackoverflow.com/questions/15843525/how-do-you-insert-the-value-in-a-sorted-vector)
// https://en.cppreference.com/w/cpp/algorithm/upper_bound
