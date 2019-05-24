// https://github.com/google/glog/blob/ba8a9f6952d04d1403b97df24e6836227751454e/src/googletest.h
#pragma once

#include <cstdio>
#include <ctime>
#include <map>
#include <string>

using std::clock;
using std::clock_t;
using std::map;
using std::printf;
using std::puts;
using std::string;

#include "commandlineflags.h"
#include "mini_gtest.hpp"


DEFINE_bool(run_benchmark, true, "If true, run benchmarks");
#ifdef NDEBUG
DEFINE_int32(benchmark_iters, 100000000, "Number of iterations per benchmark");
#else
DEFINE_int32(benchmark_iters, 100000, "Number of iterations per benchmark");
#endif

#define BENCHMARK(n) static BenchmarkRegisterer __benchmark_ ## n (#n, &n);

map<string, void(*)(int)> g_benchlist;  // the benchmarks to run

class BenchmarkRegisterer {
public:
    BenchmarkRegisterer(const char* name, void(*function)(int iters)) {
        EXPECT_TRUE(g_benchlist.insert(std::make_pair(name, function)).second);
    }
};

static inline void RunSpecifiedBenchmarks() {
    if (!FLAGS_run_benchmark) {
        return;
    }

    int iter_cnt = FLAGS_benchmark_iters;
    puts("Benchmark\tTime(ns)\tIterations");
    for (map<string, void(*)(int)>::const_iterator iter = g_benchlist.begin();
        iter != g_benchlist.end();
        ++iter) {
        clock_t start = clock();
        iter->second(iter_cnt);
        double elapsed_ns =
            ((double)clock() - start) / CLOCKS_PER_SEC * 1000 * 1000 * 1000;
        printf("%s\t%8.2lf\t%10d\n",
            iter->first.c_str(), elapsed_ns / iter_cnt, iter_cnt);
    }
    puts("");
}
