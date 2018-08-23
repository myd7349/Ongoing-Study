#ifndef DATA_RATE_UNIT_
#define DATA_RATE_UNIT_

#include <assert.h>
#include <stdint.h>

#include "../algutils.h"

C_API_BEGIN

typedef enum
{
    bps,
    kbps,
    Mbps,
    Gbps,
    Tbps,
    // ----
    Bps,
    KBps,
    MBps,
    GBps,
    TBps,
    // ----
    KiBps,
    MiBps,
    GiBps,
    TiBps,
} data_rate_unit_t;


static uint64_t data_rate_convert(uint64_t data_rate, data_rate_unit_t from, data_rate_unit_t to)
{
    static uint64_t data_rate_factors[] =
    {
        1,                               // 1 bps == 1 bps
        1000,                            // 1 kbps == 1000 bps
        1000000,                         // 1 Mbps
        1000000000,                      // 1 Gbps
        1000000000000LL,                 // 1 Tbps
        // ---------------------------------------------------
        8,                               // 1 Bps == 8 bps
        1000 * 8,                        // 1 KB/s
        1000000 * 8,                     // 1 MB/s
        1000000000LL * 8,                  // 1 GB/s
        1000000000000LL * 8,             // 1 TB/s
        // ---------------------------------------------------
        1024 * 8,                        // 1 KiB
        1024 * 1024 * 8,                 // 1 MiB
        1024LL * 1024 * 1024 * 8,        // 1 GiB
        1024LL * 1024 * 1024 * 1024 * 8  // 1 TiB
    };

    assert(ARRAYSIZE(data_rate_factors) == TiBps + 1);
    assert(from >= bps && from <= TiBps);
    assert(to >= bps && to <= TiBps);

    return data_rate * data_rate_factors[from] / data_rate_factors[to];
}


static long double data_rate_convertf(long double data_rate, data_rate_unit_t from, data_rate_unit_t to)
{
    static long double data_rate_factors[] =
    {
        1,                               // 1 bps == 1 bps
        1000,                            // 1 kbps == 1000 bps
        1000000,                         // 1 Mbps
        1000000000,                      // 1 Gbps
        1000000000000LL,                 // 1 Tbps
        // ---------------------------------------------------
        8,                               // 1 Bps == 8 bps
        1000 * 8,                        // 1 KB/s
        1000000 * 8,                     // 1 MB/s
        1000000000LL * 8,                  // 1 GB/s
        1000000000000LL * 8,             // 1 TB/s
        // ---------------------------------------------------
        1024 * 8,                        // 1 KiB
        1024 * 1024 * 8,                 // 1 MiB
        1024LL * 1024 * 1024 * 8,        // 1 GiB
        1024LL * 1024 * 1024 * 1024 * 8  // 1 TiB
    };

    assert(ARRAYSIZE(data_rate_factors) == TiBps + 1);
    assert(from >= bps && from <= TiBps);
    assert(to >= bps && to <= TiBps);

    return data_rate * data_rate_factors[from] / data_rate_factors[to];
}


static const char *data_rate_unit_name(data_rate_unit_t unit)
{
    const char *names[] =
    {
        "bps",
        "kbps",
        "Mbps",
        "Gbps",
        "Tbps",
        // ----
        "Bps",
        "KB/s",
        "MB/s",
        "GB/s",
        "TB/s",
        // ----
        "KiB/s",
        "MiB/s",
        "GiB/s",
        "TiB/s",
    };

    assert(unit >= bps && unit <= TiBps);
    return names[unit];
}


C_API_END

#endif // DATA_RATE_UNIT_


// References:
// https://en.wikipedia.org/wiki/Data-rate_units
// https://en.wikipedia.org/wiki/Kibibyte
