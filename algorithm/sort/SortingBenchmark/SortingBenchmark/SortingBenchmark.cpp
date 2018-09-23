// 2018-07-05T12:05+08:00
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iterator>
#include <random>

#include <benchmark/benchmark.h>

#include "../../../../cpp/common.h"

extern "C"
{
#include "../../bubble_sort/bubble_sort.h"
#include "../../insert_sort/insert_sort.h"
#include "../../merge_sort/merge_sort.h"
#include "../../quick_sort/quick_sort.h"
#include "../../radix_sort/radix_sort.h"
#include "../../selection_sort/selection_sort.h"
}


#ifdef _MSC_VER
# pragma comment(lib, "shlwapi.lib")
#endif


void DumpData(const char *filename, const std::vector<int> &data)
{
    std::ofstream out(filename);
    if (out.is_open())
    {
        std::copy(data.cbegin(), data.cend(),
            std::ostream_iterator<int>(out, "\n"));
        out.close();
    }
}


struct Data
{
    Data(int length)
        : raw_data(length), data(length), temp(length)
    {
        std::random_device rd;
        std::mt19937 g(rd());

        std::generate(raw_data.begin(), raw_data.end(), g);
        DumpData("BM_RawData.txt", raw_data);

        std::copy(raw_data.cbegin(), raw_data.cend(), data.begin());
        std::sort(data.begin(), data.end());
        DumpData("BM_SortedData.txt", data);
    }

    void Prepare()
    {
        std::copy(raw_data.cbegin(), raw_data.cend(), data.begin());
    }

    std::vector<int> raw_data;
    std::vector<int> data;
    std::vector<int> temp;
};


const int Length = 2048;

static Data data(Length);


bool IsSortedOf(const std::vector<int> &data, const std::vector<int> &raw_data)
{
    std::vector<int> temp(raw_data.cbegin(), raw_data.cend());
    std::sort(temp.begin(), temp.end());
    return std::equal(data.cbegin(), data.cend(), temp.cbegin());
}


static int CompareInt(const void *x, const void *y)
{
    assert(x != NULL && y != NULL);

#if 0
    // erroneous (fails if INT_MIN is present)
    return *(const int *)x - *(const int *)y;
#else
    int arg1 = *(const int *)x;
    int arg2 = *(const int *)y;
    return CMP(arg1, arg2);
#endif
}


static void STLSort(std::vector<int> &data, std::vector<int> &)
{
    std::sort(data.begin(), data.end());
}


static void STLSort_WithPred(std::vector<int> &data, std::vector<int> &)
{
    std::sort(data.begin(), data.end(), std::less<int>());
}


static void BubbleSort(std::vector<int> &data, std::vector<int> &)
{
    bubble_sorti(
        reinterpret_cast<int *>(data.data()),
        static_cast<int>(data.size()));
}


static void BubbleSort_optimized(std::vector<int> &data, std::vector<int> &)
{
    optimized_bubble_sorti(
        reinterpret_cast<int *>(data.data()),
        static_cast<int>(data.size()));
}


static void InsertSort(std::vector<int> &data, std::vector<int> &)
{
    insert_sort(
        static_cast<void *>(data.data()),
        static_cast<unsigned>(data.size()),
        static_cast<unsigned>(sizeof(int)),
        CompareInt);
}


static void InsertSort_old_school(std::vector<int> &data, std::vector<int> &)
{
    insert_sorti_old_school(
        data.data(),
        static_cast<unsigned>(data.size()));
}


static void MergeSort(std::vector<int> &data, std::vector<int> &temp)
{
    top_down_merge_sorti(
        reinterpret_cast<int *>(data.data()),
        static_cast<int>(data.size()),
        reinterpret_cast<int *>(temp.data()));
}


static void QuickSort_LomutoPartition_first(std::vector<int> &data, std::vector<int> &)
{
    lomuto_partition_quick_sorti(
        reinterpret_cast<int *>(data.data()),
        static_cast<int>(data.size()),
        first);
}


static void QuickSort_LomutoPartition_last(std::vector<int> &data, std::vector<int> &)
{
    lomuto_partition_quick_sorti(
        reinterpret_cast<int *>(data.data()),
        static_cast<int>(data.size()),
        last);
}


static void QuickSort_LomutoPartition_middle(std::vector<int> &data, std::vector<int> &)
{
    lomuto_partition_quick_sorti(
        reinterpret_cast<int *>(data.data()),
        static_cast<int>(data.size()),
        middle);
}


static void QuickSort_LomutoPartition_middle_of_three(std::vector<int> &data, std::vector<int> &)
{
    lomuto_partition_quick_sorti(
        reinterpret_cast<int *>(data.data()),
        static_cast<int>(data.size()),
        middle_of_three);
}


static void QuickSort_LomutoPartition_random_chooser(std::vector<int> &data, std::vector<int> &)
{
    lomuto_partition_quick_sorti(
        reinterpret_cast<int *>(data.data()),
        static_cast<int>(data.size()),
        random_chooser);
}


static void QuickSort_HoarePartition_first(std::vector<int> &data, std::vector<int> &)
{
    hoare_partition_quick_sorti(
        reinterpret_cast<int *>(data.data()),
        static_cast<int>(data.size()),
        first);
}


static void QuickSort_HoarePartition_last(std::vector<int> &data, std::vector<int> &)
{
    hoare_partition_quick_sorti(
        reinterpret_cast<int *>(data.data()),
        static_cast<int>(data.size()),
        last);
}


static void QuickSort_HoarePartition_middle(std::vector<int> &data, std::vector<int> &)
{
    hoare_partition_quick_sorti(
        reinterpret_cast<int *>(data.data()),
        static_cast<int>(data.size()),
        middle);
}


static void QuickSort_HoarePartition_middle_of_three(std::vector<int> &data, std::vector<int> &)
{
    hoare_partition_quick_sorti(
        reinterpret_cast<int *>(data.data()),
        static_cast<int>(data.size()),
        middle_of_three);
}


static void QuickSort_HoarePartition_random_chooser(std::vector<int> &data, std::vector<int> &)
{
    hoare_partition_quick_sorti(
        reinterpret_cast<int *>(data.data()),
        static_cast<int>(data.size()),
        random_chooser);
}


static void QuickSort_qsort(std::vector<int> &data, std::vector<int> &)
{
    std::qsort(
        static_cast<void *>(data.data()),
        static_cast<size_t>(data.size()),
        sizeof(int),
        CompareInt);
}


static void RadixSort_Base10(std::vector<int> &data, std::vector<int> &)
{
    radix_sorti10(
        reinterpret_cast<int *>(data.data()),
        static_cast<int>(data.size()));
}


static void RadixSort_Base16(std::vector<int> &data, std::vector<int> &)
{
    radix_sorti(
        reinterpret_cast<int *>(data.data()),
        static_cast<int>(data.size()),
        16);
}


static void RadixSort_Base256(std::vector<int> &data, std::vector<int> &)
{
    radix_sorti(
        reinterpret_cast<int *>(data.data()),
        static_cast<int>(data.size()),
        256);
}


static void SelectionSort(std::vector<int> &data, std::vector<int> &)
{
    selection_sorti(
        reinterpret_cast<int *>(data.data()),
        static_cast<unsigned>(data.size()));
}


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
        sort(data.data, data.temp); \
        \
        state.PauseTiming(); \
        if (!IsSortedOf(data.data, data.raw_data)) \
        { \
            DumpData(name, data.data); \
            \
            STLSort(data.data, data.temp); \
            if (IsSortedOf(data.data, data.raw_data)) \
                state.SkipWithError("Opps! Not sorted."); \
            else \
                state.SkipWithError("Opps! Data broken."); \
        } \
        state.ResumeTiming();\
    } \
} \
\
BENCHMARK(BM_##sort)/*->RangeMultiplier(2)->Range(1<<10, 1<<18)->Complexity(benchmark::oN)*/;


DEFINE_SORTING_BENCHMARK(STLSort);
DEFINE_SORTING_BENCHMARK(STLSort_WithPred);
DEFINE_SORTING_BENCHMARK(BubbleSort);
DEFINE_SORTING_BENCHMARK(BubbleSort_optimized);
DEFINE_SORTING_BENCHMARK(InsertSort);
DEFINE_SORTING_BENCHMARK(InsertSort_old_school);
DEFINE_SORTING_BENCHMARK(MergeSort);
DEFINE_SORTING_BENCHMARK(QuickSort_LomutoPartition_first);
DEFINE_SORTING_BENCHMARK(QuickSort_LomutoPartition_last);
DEFINE_SORTING_BENCHMARK(QuickSort_LomutoPartition_middle);
DEFINE_SORTING_BENCHMARK(QuickSort_LomutoPartition_middle_of_three);
DEFINE_SORTING_BENCHMARK(QuickSort_LomutoPartition_random_chooser);
DEFINE_SORTING_BENCHMARK(QuickSort_HoarePartition_first);
DEFINE_SORTING_BENCHMARK(QuickSort_HoarePartition_last);
DEFINE_SORTING_BENCHMARK(QuickSort_HoarePartition_middle);
DEFINE_SORTING_BENCHMARK(QuickSort_HoarePartition_middle_of_three);
DEFINE_SORTING_BENCHMARK(QuickSort_HoarePartition_random_chooser);
DEFINE_SORTING_BENCHMARK(QuickSort_qsort);
DEFINE_SORTING_BENCHMARK(RadixSort_Base10);
DEFINE_SORTING_BENCHMARK(RadixSort_Base16);
DEFINE_SORTING_BENCHMARK(RadixSort_Base256);
DEFINE_SORTING_BENCHMARK(SelectionSort);


BENCHMARK_MAIN();


// References:
// https://stackoverflow.com/questions/262000/best-algorithm-to-check-whether-a-vector-is-sorted
// https://github.com/google/benchmark
// cppreference:qsort

/*
Run on (8 X 3408 MHz CPU s)
07/05/18 14:33:55
------------------------------------------------------------------------------------
Benchmark                                             Time           CPU Iterations
------------------------------------------------------------------------------------
BM_STLSort                                        99376 ns      97656 ns       6400
BM_BubbleSort                                   3854791 ns    3840782 ns        179
BM_BubbleSort_optimized                         2937298 ns    2929688 ns        224
BM_InsertSort                                   1367672 ns    1380522 ns        498
BM_MergeSort                                     145903 ns     144385 ns       4978
BM_QuickSort_LomutoPartition_first               100592 ns      98349 ns       7467
BM_QuickSort_LomutoPartition_last                 94954 ns      96257 ns       7467
BM_QuickSort_LomutoPartition_middle              101281 ns      97656 ns       6400
BM_QuickSort_LomutoPartition_middle_of_three      95039 ns      94164 ns       7467
BM_QuickSort_LomutoPartition_random_chooser      143753 ns     139509 ns       5600
BM_QuickSort_HoarePartition_first                 94665 ns      94164 ns       7467
BM_QuickSort_HoarePartition_last                 101789 ns     102534 ns       7467
BM_QuickSort_HoarePartition_middle               100910 ns     100442 ns       7467
BM_QuickSort_HoarePartition_middle_of_three       90684 ns      89979 ns       7467
BM_QuickSort_HoarePartition_random_chooser       145294 ns     142997 ns       4480
BM_QuickSort_qsort                               235322 ns     235395 ns       2987
BM_RadixSort_Base10                              276071 ns     276215 ns       2489
BM_RadixSort_Base16                              238143 ns     240626 ns       2987
BM_RadixSort_Base256                             124870 ns     122768 ns       5600
BM_SelectionSort                                4248626 ns    4199219 ns        160

Run on (8 X 3408 MHz CPU s)
07/05/18 14:37:15
------------------------------------------------------------------------------------
Benchmark                                             Time           CPU Iterations
------------------------------------------------------------------------------------
BM_STLSort                                        91603 ns      89979 ns       7467
BM_BubbleSort                                   3728801 ns    3676471 ns        187
BM_BubbleSort_optimized                         2814209 ns    2823795 ns        249
BM_InsertSort                                   1369716 ns    1349147 ns        498
BM_MergeSort                                     136102 ns     136719 ns       5600
BM_QuickSort_LomutoPartition_first                95021 ns      94164 ns       7467
BM_QuickSort_LomutoPartition_last                 90577 ns      89979 ns       7467
BM_QuickSort_LomutoPartition_middle               92601 ns      92072 ns       7467
BM_QuickSort_LomutoPartition_middle_of_three      91043 ns      89979 ns       7467
BM_QuickSort_LomutoPartition_random_chooser      134025 ns     134969 ns       4978
BM_QuickSort_HoarePartition_first                 91340 ns      92072 ns       7467
BM_QuickSort_HoarePartition_last                  96655 ns      96257 ns       7467
BM_QuickSort_HoarePartition_middle                94829 ns      94164 ns       7467
BM_QuickSort_HoarePartition_middle_of_three       85645 ns      85794 ns       7467
BM_QuickSort_HoarePartition_random_chooser       139927 ns     138108 ns       4978
BM_QuickSort_qsort                               229477 ns     229492 ns       3200
BM_RadixSort_Base10                              266425 ns     266841 ns       2635
BM_RadixSort_Base16                              216612 ns     214844 ns       3200
BM_RadixSort_Base256                             122896 ns     122768 ns       5600
BM_SelectionSort                                4088585 ns    4087936 ns        172
*/
