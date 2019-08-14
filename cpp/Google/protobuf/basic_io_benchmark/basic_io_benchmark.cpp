#include <cstdint>
#include <cstdio>
#include <fstream>
#include <mutex>
#include <vector>

#include <benchmark/benchmark.h>

#include "data_file.pb.h"


// simdjson/common_defs.h
#ifdef _MSC_VER
# define ALWAYS_INLINE __forceinline
#else
# define ALWAYS_INLINE inline __attribute__((always_inline, unused))
#endif


constexpr int Channels = 20;
constexpr int BytesOfADC = 2; // 16-bit


ALWAYS_INLINE constexpr int operator ""_KB(std::uint64_t kB)
{
    return static_cast<int>(kB) * 1024;
}


ALWAYS_INLINE constexpr int operator ""_MB(std::uint64_t mB)
{
    return static_cast<int>(mB) * 1024_KB;
}


static const char *tmpnam_t(char(&fileName)[L_tmpnam])
{
    static std::mutex mutex;

    std::lock_guard<std::mutex> lck(mutex);
    return std::tmpnam(fileName);
}


static void RawDataFilePrepare(benchmark::State &state, bool reserve)
{
    auto expectedFileSizeInBytes = static_cast<int>(state.range(0));
    const auto samples = expectedFileSizeInBytes / Channels / BytesOfADC;

    for (auto _ : state)
    {
        state.PauseTiming();

        RawDataFile rawDataFile;
        rawDataFile.set_channels(Channels);

        if (reserve)
            rawDataFile.mutable_data()->Reserve(samples * Channels);

        state.ResumeTiming();

        for (int i = 0; i < samples; ++i)
        {
            for (int j = 0; j < Channels; ++j)
            {
                rawDataFile.add_data(i << 29 | j);
            }
        }
    }
}
BENCHMARK_CAPTURE(RawDataFilePrepare, NoReserve, false)
    ->Arg(1_KB)
    ->Arg(1_MB)
    ->Arg(16_MB)
    ->Arg(32_MB)
    ->Arg(64_MB)
    ->Arg(128_MB)
    ->Unit(benchmark::TimeUnit::kMillisecond);
BENCHMARK_CAPTURE(RawDataFilePrepare, Reserve, true)
    ->Arg(1_KB)
    ->Arg(1_MB)
    ->Arg(16_MB)
    ->Arg(32_MB)
    ->Arg(64_MB)
    ->Arg(128_MB)
    ->Unit(benchmark::TimeUnit::kMillisecond);


static void ArrayPrepare(benchmark::State &state)
{
    auto expectedFileSizeInBytes = static_cast<int>(state.range(0));
    const auto samples = expectedFileSizeInBytes / Channels / BytesOfADC;

    for (auto _ : state)
    {
        state.PauseTiming();

        std::vector<int> data(samples * Channels);

        state.ResumeTiming();

        for (int i = 0; i < samples; ++i)
        {
            for (int j = 0; j < Channels; ++j)
                data[i * Channels + j] = i << 29 | j;
        }
    }
}
BENCHMARK(ArrayPrepare)
    ->Arg(1_KB)
    ->Arg(1_MB)
    ->Arg(16_MB)
    ->Arg(32_MB)
    ->Arg(64_MB)
    ->Arg(128_MB)
    ->Unit(benchmark::TimeUnit::kMillisecond);


#if 0
class FileWritingFixture : public benchmark::Fixture
{
public:
    void SetUp(const ::benchmark::State &state) override
    {
        expectedFileSizeInBytes_ = static_cast<int>(state.range(0)); // Not work here!
        samples_ = expectedFileSizeInBytes_ / Channels / BytesOfADC;

        rawDataFile_.set_channels(Channels);
        rawDataFile_.mutable_data()->Reserve(samples_ * Channels);

        for (int i = 0; i < samples_; ++i)
        {
            for (int j = 0; j < Channels; ++j)
                rawDataFile_.add_data(i << 29 | j);
        }

        tmpFileCreated_ = tmpnam_t(fileName_) != nullptr;
    }

    void TearDown(const ::benchmark::State &) override
    {
        if (tmpFileCreated_)
            std::remove(fileName_);
    }

protected:
    int expectedFileSizeInBytes_;
    int samples_;
    RawDataFile rawDataFile_;
    char fileName_[L_tmpnam];
    bool tmpFileCreated_;
};


BENCHMARK_F(FileWritingFixture, RawDataFileWrite)(benchmark::State &state)
{
    if (!tmpFileCreated_)
        state.SkipWithError("Failed to get a temporary file name.");

    for (auto _ : state)
    {
        std::ofstream outStream(fileName_, std::ios::binary);
        if (!outStream.is_open())
            state.SkipWithError("Unable to write to file.");

        rawDataFile_.SerializeToOstream(&outStream);
    }
}
BENCHMARK_REGISTER_F(FileWritingFixture, RawDataFileWrite)
#else
static void RawDataFileWrite(benchmark::State &state)
{
    int expectedFileSizeInBytes = static_cast<int>(state.range(0));
    const int samples = expectedFileSizeInBytes / Channels / BytesOfADC;

    RawDataFile rawDataFile;
    rawDataFile.set_channels(Channels);
    rawDataFile.mutable_data()->Reserve(samples * Channels);

    for (int i = 0; i < samples; ++i)
    {
        for (int j = 0; j < Channels; ++j)
            rawDataFile.add_data(i << 29 | j);
    }

    char fileName[L_tmpnam];
    if (tmpnam_t(fileName) == nullptr)
        state.SkipWithError("Failed to get a temporary file name.");

    for (auto _ : state)
    {
        std::ofstream outStream(fileName, std::ios::binary);
        if (!outStream.is_open())
            state.SkipWithError("Unable to write to file.");

        rawDataFile.SerializeToOstream(&outStream);
    }
}
BENCHMARK(RawDataFileWrite)
#endif
    ->Arg(1_KB)
    ->Arg(1_MB)
    ->Arg(16_MB)
    ->Arg(32_MB)
    ->Arg(64_MB)
    ->Arg(128_MB)
    ->Unit(benchmark::TimeUnit::kMillisecond);


static void StdIo1dArrayWriteByLooping(benchmark::State &state)
{
    auto expectedFileSizeInBytes = static_cast<int>(state.range(0));
    const auto samples = expectedFileSizeInBytes / Channels / BytesOfADC;

    std::vector<int> data(Channels * samples);

    for (int i = 0; i < Channels; ++i)
    {
        for (int j = 0; j < samples; ++j)
            data[j * Channels + i] = i << 29 | j;
    }

    char fileName[L_tmpnam];
    if (tmpnam_t(fileName) == nullptr)
        state.SkipWithError("Failed to get a temporary file name.");

    for (auto _ : state)
    {
        std::ofstream outStream(fileName, std::ios::binary);
        if (!outStream.is_open())
            state.SkipWithError("Unable to write to file.");

        for (int i = 0; i < samples; ++i)
        {
            for (int j = 0; j < Channels; ++j)
                outStream.write(reinterpret_cast<const char *>(&data[i * Channels + j]), sizeof(int));
        }
    }

    std::remove(fileName);
}
BENCHMARK(StdIo1dArrayWriteByLooping)
    ->Arg(1_KB)
    ->Arg(1_MB)
    ->Arg(16_MB)
    ->Arg(32_MB)
    ->Arg(64_MB)
    ->Arg(128_MB)
    ->Unit(benchmark::TimeUnit::kMillisecond);


static void StdIo1dArrayWriteByLoopingV2(benchmark::State &state)
{
    auto expectedFileSizeInBytes = static_cast<int>(state.range(0));
    const auto samples = expectedFileSizeInBytes / Channels / BytesOfADC;

    std::vector<int> data(Channels * samples);

    for (int i = 0; i < Channels; ++i)
    {
        for (int j = 0; j < samples; ++j)
            data[j * Channels + i] = i << 29 | j;
    }

    char fileName[L_tmpnam];
    if (tmpnam_t(fileName) == nullptr)
        state.SkipWithError("Failed to get a temporary file name.");

    for (auto _ : state)
    {
        std::ofstream outStream(fileName, std::ios::binary);
        if (!outStream.is_open())
            state.SkipWithError("Unable to write to file.");

        for (int i = 0; i < Channels; ++i)
        {
            for (int j = 0; j < samples; ++j)
                outStream.write(reinterpret_cast<const char *>(&data[j * Channels + i]), sizeof(int));
        }
    }

    std::remove(fileName);
}
BENCHMARK(StdIo1dArrayWriteByLoopingV2)
    ->Arg(1_KB)
    ->Arg(1_MB)
    ->Arg(16_MB)
    ->Arg(32_MB)
    ->Arg(64_MB)
    ->Arg(128_MB)
    ->Unit(benchmark::TimeUnit::kMillisecond);


static void StdIo1dArrayWriteNoLooping(benchmark::State &state)
{
    auto expectedFileSizeInBytes = static_cast<int>(state.range(0));
    const auto samples = expectedFileSizeInBytes / Channels / BytesOfADC;

    std::vector<int> data(Channels * samples);

    for (int i = 0; i < Channels; ++i)
    {
        for (int j = 0; j < samples; ++j)
            data[j * Channels + i] = i << 29 | j;
    }

    char fileName[L_tmpnam];
    if (tmpnam_t(fileName) == nullptr)
        state.SkipWithError("Failed to get a temporary file name.");

    for (auto _ : state)
    {
        std::ofstream outStream(fileName, std::ios::binary);
        if (!outStream.is_open())
            state.SkipWithError("Unable to write to file.");

        outStream.write(reinterpret_cast<const char *>(data.data()), data.size() * sizeof(int));
    }

    std::remove(fileName);
}
BENCHMARK(StdIo1dArrayWriteNoLooping)
    ->Arg(1_KB)
    ->Arg(1_MB)
    ->Arg(16_MB)
    ->Arg(32_MB)
    ->Arg(64_MB)
    ->Arg(128_MB)
    ->Unit(benchmark::TimeUnit::kMillisecond);


static void RawDataFileRead(benchmark::State &state)
{
    auto expectedFileSizeInBytes = static_cast<int>(state.range(0));
    const auto samples = expectedFileSizeInBytes / Channels / BytesOfADC;

    char fileName[L_tmpnam];
    if (tmpnam_t(fileName) == nullptr)
        state.SkipWithError("Failed to get a temporary file name.");

    {
        RawDataFile rawDataFile;
        rawDataFile.set_channels(Channels);
        rawDataFile.mutable_data()->Reserve(samples * Channels);

        for (int i = 0; i < samples; ++i)
        {
            for (int j = 0; j < Channels; ++j)
                rawDataFile.add_data(i << 29 | j);
        }

        std::ofstream outStream(fileName, std::ios::binary);
        if (outStream.is_open())
            rawDataFile.SerializeToOstream(&outStream);
        else
            state.SkipWithError("Unable to write to file.");
    }

    for (auto _ : state)
    {
        RawDataFile rawDataFile;

        std::ifstream inStream(fileName, std::ios::binary);
        if (inStream.is_open())
            rawDataFile.ParseFromIstream(&inStream);
        else
            state.SkipWithError("Unable to parse input stream.");
    }

    std::remove(fileName);
}
BENCHMARK(RawDataFileRead)
    ->Arg(1_KB)
    ->Arg(1_MB)
    ->Arg(16_MB)
    ->Arg(32_MB)
    ->Arg(64_MB)
    ->Arg(128_MB)
    ->Unit(benchmark::TimeUnit::kMillisecond);


static void StdIoReadTo2dArray(benchmark::State &state)
{
    auto expectedFileSizeInBytes = static_cast<int>(state.range(0));
    const auto samples = expectedFileSizeInBytes / Channels / BytesOfADC;

    char fileName[L_tmpnam];
    if (tmpnam_t(fileName) == nullptr)
        state.SkipWithError("Failed to get a temporary file name.");

    std::ofstream outStream(fileName, std::ios::binary);
    if (!outStream.is_open())
        state.SkipWithError("Unable to write to file.");

    int num;

    for (int i = 0; i < samples; ++i)
    {
        for (int j = 0; j < Channels; ++j)
        {
            num = i << 29 | j;
            outStream.write(reinterpret_cast<const char *>(&num), sizeof(num));
        }
    }

    std::vector<std::vector<int>> data(Channels);
    for (auto &channelData : data)
        channelData.resize(samples);

    for (auto _ : state)
    {
        std::ifstream inStream(fileName, std::ios::binary);
        if (!inStream.is_open())
            state.SkipWithError("Unable to parse input stream.");

        for (int i = 0; i < samples; ++i)
        {
            for (int j = 0; j < Channels; ++j)
                inStream.read(reinterpret_cast<char *>(&data[j][i]), sizeof(int));
        }
    }

    std::remove(fileName);
}
BENCHMARK(StdIoReadTo2dArray)
    ->Arg(1_KB)
    ->Arg(1_MB)
    ->Arg(16_MB)
    ->Arg(32_MB)
    ->Arg(64_MB)
    ->Arg(128_MB)
    ->Unit(benchmark::TimeUnit::kMillisecond);


static void StdIoReadTo1dArray(benchmark::State &state)
{
    auto expectedFileSizeInBytes = static_cast<int>(state.range(0));
    const auto samples = expectedFileSizeInBytes / Channels / BytesOfADC;

    char fileName[L_tmpnam];
    if (tmpnam_t(fileName) == nullptr)
        state.SkipWithError("Failed to get a temporary file name.");

    std::ofstream outStream(fileName, std::ios::binary);
    if (!outStream.is_open())
        state.SkipWithError("Unable to write to file.");

    int num;

    for (int i = 0; i < samples; ++i)
    {
        for (int j = 0; j < Channels; ++j)
        {
            num = i << 29 | j;
            outStream.write(reinterpret_cast<const char *>(&num), sizeof(num));
        }
    }

    std::vector<int> rawData(samples * Channels);

    for (auto _ : state)
    {
        std::ifstream inStream(fileName, std::ios::binary);
        if (!inStream.is_open())
            state.SkipWithError("Unable to parse input stream.");

        inStream.read(reinterpret_cast<char *>(rawData.data()), rawData.size() * sizeof(int));
    }

    std::remove(fileName);
}
BENCHMARK(StdIoReadTo1dArray)
    ->Arg(1_KB)
    ->Arg(1_MB)
    ->Arg(16_MB)
    ->Arg(32_MB)
    ->Arg(64_MB)
    ->Arg(128_MB)
    ->Unit(benchmark::TimeUnit::kMillisecond);


static void RawDataFileCopyToArray(benchmark::State &state)
{
    auto expectedFileSizeInBytes = static_cast<int>(state.range(0));
    const auto samples = expectedFileSizeInBytes / Channels / BytesOfADC;

    char fileName[L_tmpnam];
    if (tmpnam_t(fileName) == nullptr)
        state.SkipWithError("Failed to get a temporary file name.");

    {
        RawDataFile rawDataFile;
        rawDataFile.set_channels(Channels);
        rawDataFile.mutable_data()->Reserve(samples * Channels);

        for (int i = 0; i < samples; ++i)
        {
            for (int j = 0; j < Channels; ++j)
                rawDataFile.add_data(i << 29 | j);
        }

        std::ofstream outStream(fileName, std::ios::binary);
        if (outStream.is_open())
            rawDataFile.SerializeToOstream(&outStream);
        else
            state.SkipWithError("Unable to write to file.");
    }

    {
        RawDataFile rawDataFile;

        std::ifstream inStream(fileName, std::ios::binary);
        if (inStream.is_open())
            rawDataFile.ParseFromIstream(&inStream);
        else
            state.SkipWithError("Unable to parse input stream.");

        std::vector<std::vector<int>> data(Channels);
        for (auto &channelData : data)
            channelData.resize(samples);
        
        for (auto _ : state)
        {
            for (int i = 0; i < Channels; ++i)
            {
                for (int j = 0; j < samples; ++j)
                    data[i][j] = rawDataFile.data()[j * Channels + i];
            }
        }
    }

    std::remove(fileName);
}
BENCHMARK(RawDataFileCopyToArray)
    ->Arg(1_KB)
    ->Arg(1_MB)
    ->Arg(16_MB)
    ->Arg(32_MB)
    ->Arg(64_MB)
    ->Arg(128_MB)
    ->Unit(benchmark::TimeUnit::kMillisecond);


static void ArrayCopyToArray(benchmark::State &state)
{
    auto expectedFileSizeInBytes = static_cast<int>(state.range(0));
    const auto samples = expectedFileSizeInBytes / Channels / BytesOfADC;

    char fileName[L_tmpnam];
    if (tmpnam_t(fileName) == nullptr)
        state.SkipWithError("Failed to get a temporary file name.");

    std::ofstream outStream(fileName, std::ios::binary);
    if (!outStream.is_open())
        state.SkipWithError("Unable to write to file.");

    int num;

    for (int i = 0; i < samples; ++i)
    {
        for (int j = 0; j < Channels; ++j)
        {
            num = i << 29 | j;
            outStream.write(reinterpret_cast<const char *>(&num), sizeof(num));
        }
    }

    {
        std::ifstream inStream(fileName, std::ios::binary);
        if (!inStream.is_open())
            state.SkipWithError("Unable to parse input stream.");

        std::vector<int> rawData(samples * Channels);
        inStream.read(reinterpret_cast<char *>(rawData.data()), rawData.size() * sizeof(int));

        std::vector<std::vector<int>> data(Channels);
        for (auto &channelData : data)
            channelData.resize(samples);

        for (auto _ : state)
        {
            for (int i = 0; i < Channels; ++i)
            {
                for (int j = 0; j < samples; ++j)
                    data[i][j] = rawData[j * Channels + i];
            }
        }
    }

    std::remove(fileName);
}
BENCHMARK(ArrayCopyToArray)
    ->Arg(1_KB)
    ->Arg(1_MB)
    ->Arg(16_MB)
    ->Arg(32_MB)
    ->Arg(64_MB)
    ->Arg(128_MB)
    ->Unit(benchmark::TimeUnit::kMillisecond);


// References:
// https://stackoverflow.com/questions/4090173/using-protobuf-net-how-to-deserialize-a-multi-dimensional-array
// https://stackoverflow.com/questions/10032998/benchmark-the-performance-of-file-systems
// https://stackoverflow.com/questions/237804/what-new-capabilities-do-user-defined-literals-add-to-c
// https://stackoverflow.com/questions/16851948/posix-extended-definition-of-reentrancy-covering-thread-safety
