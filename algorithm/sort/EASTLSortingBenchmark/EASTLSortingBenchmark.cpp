// 2018-07-05T12:05+08:00
#include <cstdlib>
#include <random>

#include <benchmark/benchmark.h>

#include <EASTL/algorithm.h>
#include <EASTL/random.h>
#include <EASTL/sort.h>
#include <EASTL/vector.h>

#include "../../algutils.h"


#ifdef _MSC_VER
# pragma comment(lib, "EASTL.lib")
# pragma comment(lib, "shlwapi.lib")
#endif


DEFINE_COMPARE_T(int, CompareInt)


struct Data
{
    Data(int length)
        : raw_data(length), data(length)
    {
        std::random_device rd;
        std::mt19937 g(rd());

        for (auto &v : raw_data)
            v = static_cast<int>(g());

        eastl::copy(raw_data.cbegin(), raw_data.cend(), data.begin());
    }

    void Prepare()
    {
        eastl::copy(raw_data.cbegin(), raw_data.cend(), data.begin());
    }

    eastl::vector<int> raw_data;
    eastl::vector<int> data;
};


const int Length = 2048;

static Data data(Length);


static void STLSort(eastl::vector<int> &data)
{
    std::sort(data.begin(), data.end());
}


static void STLSort_WithPred(eastl::vector<int> &data)
{
    std::sort(data.begin(), data.end(), std::less<int>());
}


static void C_qsort(eastl::vector<int> &data)
{
    std::qsort(
        static_cast<void *>(data.data()),
        static_cast<size_t>(data.size()),
        sizeof(int),
        CompareInt);
}


#define DEFINE_EASTL_SORT_WRAPPER(sort) \
static void EASTL_##sort(eastl::vector<int> &data) \
{ \
    eastl::sort(data.begin(), data.end()); \
}


DEFINE_EASTL_SORT_WRAPPER(sort)
DEFINE_EASTL_SORT_WRAPPER(quick_sort)
//DEFINE_EASTL_SORT_WRAPPER(tim_sort)
//DEFINE_EASTL_SORT_WRAPPER(tim_sort_buffer)
DEFINE_EASTL_SORT_WRAPPER(insertion_sort)
DEFINE_EASTL_SORT_WRAPPER(shell_sort)
DEFINE_EASTL_SORT_WRAPPER(heap_sort)
DEFINE_EASTL_SORT_WRAPPER(stable_sort)
//DEFINE_EASTL_SORT_WRAPPER(merge_sort)
//DEFINE_EASTL_SORT_WRAPPER(radix_sort)
DEFINE_EASTL_SORT_WRAPPER(comb_sort)
DEFINE_EASTL_SORT_WRAPPER(bubble_sort)
//DEFINE_EASTL_SORT_WRAPPER(selection_sort)
//DEFINE_EASTL_SORT_WRAPPER(shaker_sort)
//DEFINE_EASTL_SORT_WRAPPER(bucket_sort)


#define DEFINE_SORTING_BENCHMARK(sort) \
static void BM_##sort(benchmark::State& state) \
{ \
    const char *name = STR(CONCAT(BM_, sort)) ".txt"; \
    \
    for (auto _ : state) \
    { \
        state.PauseTiming(); \
        data.Prepare(); \
        state.ResumeTiming();\
        \
        sort(data.data); \
    } \
} \
\
BENCHMARK(BM_##sort)/*->RangeMultiplier(2)->Range(1<<10, 1<<18)->Complexity(benchmark::oN)*/;


DEFINE_SORTING_BENCHMARK(STLSort);
DEFINE_SORTING_BENCHMARK(STLSort_WithPred);
DEFINE_SORTING_BENCHMARK(C_qsort);
DEFINE_SORTING_BENCHMARK(EASTL_sort);
DEFINE_SORTING_BENCHMARK(EASTL_quick_sort);


BENCHMARK_MAIN()

