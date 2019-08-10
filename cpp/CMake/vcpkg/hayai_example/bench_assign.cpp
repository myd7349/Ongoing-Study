#include <vector>

#include <hayai/hayai.hpp>

#include "data_file.pb.h"


constexpr int ExpectedFileSizeInBytes = 128 * 1024 * 1024;
constexpr int Channels = 20;
constexpr int BytesOfADC = 2; // 16-bit
constexpr int Samples = ExpectedFileSizeInBytes / Channels / BytesOfADC;


static void BM_ProtobufAssign(bool reserve)
{
    RawDataFile rawDataFile;
    rawDataFile.set_channels(Channels);

    if (reserve)
        rawDataFile.mutable_data()->Reserve(Samples * Channels);

    for (int i = 0; i < Samples; ++i)
    {
        for (int j = 0; j < Channels; ++j)
        {
            rawDataFile.add_data(i << 29 | j);
        }
    }
}

BENCHMARK(BenchAssign, ProtobufAssignNoReserve, 10, 1)
{
    BM_ProtobufAssign(false);
}


BENCHMARK(BenchAssign, ProtobufAssignReserve, 10, 1)
{
    BM_ProtobufAssign(true);
}


static void BM_ArrayAssign()
{
    std::vector<int> data(Samples * Channels);

    for (int i = 0; i < Samples; ++i)
    {
        for (int j = 0; j < Channels; ++j)
            data[i * Channels + j] = i << 29 | j;
    }
}


BENCHMARK(BenchAssign, ArrayAssign, 10, 1)
{
    BM_ArrayAssign();
}


// References:
// https://stackoverflow.com/questions/4090173/using-protobuf-net-how-to-deserialize-a-multi-dimensional-array
// https://stackoverflow.com/questions/10032998/benchmark-the-performance-of-file-systems
// https://www.bfilipek.com/2016/01/micro-benchmarking-libraries-for-c.html
// https://www.bfilipek.com/2016/05/google-benchmark-library.html
// https://github.com/fenbf/benchmarkLibsTest
