#include <cassert>
#include <numeric>
#include <vector>

#include <benchmark/benchmark.h>

#include "../../common.h"
#include "../is_unique.hpp"


constexpr int Count = 50001;


template <typename IsUniqueFunc>
static void BM_IsUnique(benchmark::State &state, IsUniqueFunc isUniqueFunc)
{
    //std::vector<double> data(Count);
    //std::iota(data.begin(), data.end(), 0);

    for (auto _ : state)
    {
        //bool isUnique = isUniqueFunc(data.begin(), data.end());
        //assert(isUnique);
    }
}


static void BM_is_unique_impl_old_school(benchmark::State &state)
{
    BM_IsUnique(state, is_unique_impl_old_school<std::vector<double>::const_iterator >);
}


static void BM_is_unique_impl_using_sort(benchmark::State &state)
{
    BM_IsUnique(state, is_unique_impl_using_sort<std::vector<double>::iterator >);
}


static void BM_is_unique_impl_with_set(benchmark::State &state)
{
    BM_IsUnique(state, is_unique_impl_with_set<std::vector<double>::const_iterator >);
}


BENCHMARK(BM_is_unique_impl_old_school);
BENCHMARK(BM_is_unique_impl_using_sort);
BENCHMARK(BM_is_unique_impl_with_set);


// References:
// https://stackoverflow.com/questions/17566141/filling-unordered-set-is-too-slow
// https://stackoverflow.com/questions/24506789/set-vs-unordered-set-for-fastest-iteration
