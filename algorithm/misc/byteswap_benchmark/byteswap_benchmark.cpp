#include <benchmark/benchmark.h>

#include "builtin_byteswap.h"
#include "otfcc_byteswap.h"
#include "psnip_byteswap.h"
#include "ya_byteswap.h"


static void BM_builtin_byteswap_u16(benchmark::State &state)
{
    for (auto _ : state)
        BYTESWAP_U16((uint16_t)0x2010);
}
BENCHMARK(BM_builtin_byteswap_u16);

static void BM_otfcc_byteswap_u16(benchmark::State &state)
{
    for (auto _ : state)
        otfcc_byteswap_u16((uint16_t)0x2010);
}
BENCHMARK(BM_otfcc_byteswap_u16);

static void BM_psnip_byteswap_u16(benchmark::State &state)
{
    for (auto _ : state)
        psnip_builtin_bswap16((uint16_t)0x2010);
}
BENCHMARK(BM_psnip_byteswap_u16);

static void BM_ya_byteswap_u16(benchmark::State &state)
{
    for (auto _ : state)
        ya_byteswap_u16((uint16_t)0x2010);
}
BENCHMARK(BM_ya_byteswap_u16);

////////////////////////////////////////////////////////////

static void BM_builtin_byteswap_u32(benchmark::State &state)
{
    for (auto _ : state)
        BYTESWAP_U32((uint32_t)0xFFFFFFFF);
}
BENCHMARK(BM_builtin_byteswap_u32);

static void BM_otfcc_byteswap_u32(benchmark::State &state)
{
    for (auto _ : state)
        otfcc_byteswap_u32((uint32_t)0xFFFFFFFF);
}
BENCHMARK(BM_otfcc_byteswap_u32);

static void BM_psnip_byteswap_u32(benchmark::State &state)
{
    for (auto _ : state)
        psnip_builtin_bswap32((uint32_t)0xFFFFFFFF);
}
BENCHMARK(BM_psnip_byteswap_u32);

static void BM_ya_byteswap_u32(benchmark::State &state)
{
    for (auto _ : state)
        ya_byteswap_u32((uint32_t)0xFFFFFFFF);
}
BENCHMARK(BM_ya_byteswap_u32);

///////////////////////////////////////////////////////////

static void BM_builtin_byteswap_u64(benchmark::State &state)
{
    for (auto _ : state)
        BYTESWAP_U64((uint64_t)0xFFFFFFFFFFFFFFFFLL);
}
BENCHMARK(BM_builtin_byteswap_u64);

static void BM_otfcc_byteswap_u64(benchmark::State &state)
{
    for (auto _ : state)
        otfcc_byteswap_u64((uint64_t)0xFFFFFFFFFFFFFFFFLL);
}
BENCHMARK(BM_otfcc_byteswap_u64);

static void BM_psnip_byteswap_u64(benchmark::State &state)
{
    for (auto _ : state)
        psnip_builtin_bswap64((uint64_t)0xFFFFFFFFFFFFFFFFLL);
}
BENCHMARK(BM_psnip_byteswap_u64);

static void BM_ya_byteswap_u64(benchmark::State &state)
{
    for (auto _ : state)
        ya_byteswap_u64((uint64_t)0xFFFFFFFFFFFFFFFFLL);
}
BENCHMARK(BM_ya_byteswap_u64);
