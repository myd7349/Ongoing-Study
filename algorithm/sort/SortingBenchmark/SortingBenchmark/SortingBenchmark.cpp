// 2018-07-05T12:05+08:00
#include <algorithm>
#include <cassert>
#include <cstdlib>
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


int CompareInt(const void *x, const void *y)
{
    assert(x != NULL && y != NULL);
    return *(const int *)x - *(const int *)y;
}


void sort(std::vector<int> &data, std::vector<int> &)
{
    std::sort(data.begin(), data.end());
}


void BubbleSort(std::vector<int> &data, std::vector<int> &)
{
    bubble_sorti(
        reinterpret_cast<int *>(data.data()),
        static_cast<int>(data.size()));
}


void InsertSort(std::vector<int> &data, std::vector<int> &)
{
    insert_sort(
        static_cast<void *>(data.data()),
        static_cast<unsigned>(data.size()),
        static_cast<unsigned>(sizeof(int)),
        CompareInt);
}


void MergeSort(std::vector<int> &data, std::vector<int> &temp)
{
    top_down_merge_sorti(
        reinterpret_cast<int *>(data.data()),
        static_cast<int>(data.size()),
        reinterpret_cast<int *>(temp.data()));
}


void QuickSort_LomutoPartition_first(std::vector<int> &data, std::vector<int> &)
{
    lomuto_partition_quick_sorti(
        reinterpret_cast<int *>(data.data()),
        static_cast<int>(data.size()),
        first);
}


void QuickSort_LomutoPartition_last(std::vector<int> &data, std::vector<int> &)
{
    lomuto_partition_quick_sorti(
        reinterpret_cast<int *>(data.data()),
        static_cast<int>(data.size()),
        last);
}


void QuickSort_LomutoPartition_middle(std::vector<int> &data, std::vector<int> &)
{
    lomuto_partition_quick_sorti(
        reinterpret_cast<int *>(data.data()),
        static_cast<int>(data.size()),
        middle);
}


void QuickSort_LomutoPartition_middle_of_three(std::vector<int> &data, std::vector<int> &)
{
    lomuto_partition_quick_sorti(
        reinterpret_cast<int *>(data.data()),
        static_cast<int>(data.size()),
        middle_of_three);
}


void QuickSort_LomutoPartition_random_chooser(std::vector<int> &data, std::vector<int> &)
{
    lomuto_partition_quick_sorti(
        reinterpret_cast<int *>(data.data()),
        static_cast<int>(data.size()),
        random_chooser);
}


void QuickSort_HoarePartition_first(std::vector<int> &data, std::vector<int> &)
{
    hoare_partition_quick_sorti(
        reinterpret_cast<int *>(data.data()),
        static_cast<int>(data.size()),
        first);
}


void QuickSort_HoarePartition_last(std::vector<int> &data, std::vector<int> &)
{
    hoare_partition_quick_sorti(
        reinterpret_cast<int *>(data.data()),
        static_cast<int>(data.size()),
        last);
}


void QuickSort_HoarePartition_middle(std::vector<int> &data, std::vector<int> &)
{
    hoare_partition_quick_sorti(
        reinterpret_cast<int *>(data.data()),
        static_cast<int>(data.size()),
        middle);
}


void QuickSort_HoarePartition_middle_of_three(std::vector<int> &data, std::vector<int> &)
{
    hoare_partition_quick_sorti(
        reinterpret_cast<int *>(data.data()),
        static_cast<int>(data.size()),
        middle_of_three);
}


void QuickSort_HoarePartition_random_chooser(std::vector<int> &data, std::vector<int> &)
{
    hoare_partition_quick_sorti(
        reinterpret_cast<int *>(data.data()),
        static_cast<int>(data.size()),
        random_chooser);
}


void QuickSort_qsort(std::vector<int> &data, std::vector<int> &)
{
    std::qsort(
        static_cast<void *>(data.data()),
        static_cast<int>(data.size()),
        static_cast<unsigned>(sizeof(int)),
        CompareInt);
}


void RadixSort_Base10(std::vector<int> &data, std::vector<int> &)
{
    radix_sorti10(
        reinterpret_cast<int *>(data.data()),
        static_cast<int>(data.size()));
}


void RadixSort_Base16(std::vector<int> &data, std::vector<int> &)
{
    radix_sorti(
        reinterpret_cast<int *>(data.data()),
        static_cast<int>(data.size()),
        16);
}


void RadixSort_Base256(std::vector<int> &data, std::vector<int> &)
{
    radix_sorti(
        reinterpret_cast<int *>(data.data()),
        static_cast<int>(data.size()),
        256);
}


void SelectionSort(std::vector<int> &data, std::vector<int> &)
{
    selection_sorti(
        reinterpret_cast<int *>(data.data()),
        static_cast<unsigned>(data.size()));
}


#define DEFINE_SORTING_BENCHMARK(sort) \
std::random_device CONCAT(sort, _rd); \
std::mt19937 CONCAT(sort, _g)(CONCAT(sort, _rd)()); \
\
static void BM_##sort(benchmark::State& state) \
{ \
    std::vector<int> data(1024); \
    std::vector<int> temp(data.size()); \
    \
    for (auto _ : state) \
    { \
        std::generate(data.begin(), data.end(), CONCAT(sort, _g)); \
        sort(data, temp); \
        if (!std::is_sorted(data.begin(), data.end())) \
            state.SkipWithError("Opps! Not sorted."); \
    } \
} \
\
BENCHMARK(BM_##sort)/*->RangeMultiplier(2)->Range(1<<10, 1<<18)->Complexity(benchmark::oN)*/;


DEFINE_SORTING_BENCHMARK(sort);
DEFINE_SORTING_BENCHMARK(BubbleSort);
DEFINE_SORTING_BENCHMARK(InsertSort);
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


BENCHMARK_MAIN()


// References:
// https://stackoverflow.com/questions/262000/best-algorithm-to-check-whether-a-vector-is-sorted
// https://github.com/google/benchmark
