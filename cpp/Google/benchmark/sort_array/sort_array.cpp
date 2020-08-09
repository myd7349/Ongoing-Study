// clang-format off
#include <algorithm>
#include <cstdlib>
#include <functional>
#include <limits>
#include <random>
#include <vector>

#include <benchmark/benchmark.h>
// clang-format on

namespace {
std::vector<unsigned> GenerateRandomNumbers(unsigned min, unsigned max,
                                            std::size_t count) {
  std::random_device rd;
  std::uniform_int_distribution<unsigned> dist(min, max);  // inclusive

  std::vector<unsigned> nums(count);
  std::generate_n(nums.begin(), count, [&] { return dist(rd); });

  return nums;
}

void SortArray(unsigned *data, std::size_t len) {
  for (std::size_t i = 0; i < len; ++i) {
    for (std::size_t j = 0; j < len - 1; ++j) {
      if (data[j] > data[j + 1]) std::swap(data[j], data[j + 1]);
    }
  }
}

void BM_SortArray(benchmark::State &state) {
  std::vector<unsigned> data =
      GenerateRandomNumbers(std::numeric_limits<unsigned>::min(),
                            std::numeric_limits<unsigned>::max(), 10000);

  while (state.KeepRunning()) {
    SortArray(data.data(), data.size());
  }
}

void BM_qsort(benchmark::State &state) {
  std::vector<unsigned> data =
      GenerateRandomNumbers(std::numeric_limits<unsigned>::min(),
                            std::numeric_limits<unsigned>::max(), 10000);

  while (state.KeepRunning()) {
    std::qsort(data.data(), data.size(), sizeof(unsigned),
               [](const void *a, const void *b) {
                 unsigned arg1 = *static_cast<const unsigned *>(a);
                 unsigned arg2 = *static_cast<const unsigned *>(b);

                 if (arg1 < arg2) return -1;
                 if (arg1 > arg2) return 1;
                 return 0;
               });
  }
}

void BM_sort(benchmark::State &state) {
  std::vector<unsigned> data =
      GenerateRandomNumbers(std::numeric_limits<unsigned>::min(),
                            std::numeric_limits<unsigned>::max(), 10000);

  while (state.KeepRunning()) {
    std::sort(data.begin(), data.end());
  }
}

void BM_sort_with_pred(benchmark::State &state) {
  std::vector<unsigned> data =
      GenerateRandomNumbers(std::numeric_limits<unsigned>::min(),
                            std::numeric_limits<unsigned>::max(), 10000);

  while (state.KeepRunning()) {
    std::sort(data.begin(), data.end(), std::less<unsigned>());
  }
}
}  // namespace

BENCHMARK(BM_SortArray);
BENCHMARK(BM_qsort);
BENCHMARK(BM_sort);
BENCHMARK(BM_sort_with_pred);

// clang-format off
// References:
// https://github.com/NAThompson/using_googlebenchmark
// Ongoing-Study\cpp\Basics\random\gen_10_random_numbers\gen_10_random_numbers.cpp
// [cppreference: qsort](https://en.cppreference.com/w/cpp/algorithm/qsort)
// https://github.com/google/benchmark/issues/397
// clang-format on
