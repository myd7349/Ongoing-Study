#include <iomanip>
#include <iostream>
#include <thread>

#include "../../../cpp/dividing_lines.h"
#undef ARRAYSIZE
#include "../../../cpp/Stopwatch.h"
#include "../../../cpp/uniform_typename/uniform_typename.h"

#include "Consumer.hpp"
#include "ConsumerContext.hpp"
#include "Producer.hpp"
#include "ProducerConsumerContextV1.hpp"
#include "ProducerConsumerContextV2.hpp"
#include "ProducerConsumerContextV3.hpp"

#ifdef _WIN32
#include "ProducerConsumerContextWin32.hpp"
#include "ProducerConsumerContextWin32V2.hpp"
#endif

#if FOUND_PTHREADS
#include "ProducerConsumerContextPThreads.hpp"
#endif


template <typename ProducerConsumerContextT>
void Test()
{
    DIVIDING_LINE_1('-');
    std::cout << TYPE_NAME(ProducerConsumerContextT) << std::endl;

    constexpr int Channels = 71;
    constexpr int BufferSize = Channels * 100000;
    constexpr int TotalSize = Channels * 4000 * 120;

    Stopwatch sw;
    sw.Start();

    ProducerConsumerContextT context(BufferSize, std::cout, ENABLE_LOGGING);
    ConsumerContext consumerContext(TotalSize, false);

    Producer producer(context, 0, TotalSize, Channels * 200 - 13);
    Consumer consumer(context, consumerContext, TotalSize, Channels * 200 + 17);

    std::thread producerThread = producer.Create();
    std::thread consumerThread = consumer.Create();

    producerThread.join();
    consumerThread.join();

    sw.Stop();
    std::cout << "Elapsed time: " << sw.GetElapsedMilliseconds() << "ms" << std::endl;

    std::cout << "Checking if test is passed...\n";

    sw.Restart();
    bool ok = consumerContext.IsTestPassed();
    sw.Stop();

    std::cout << "It takes " << sw.GetElapsedMilliseconds() << "ms to figure out if test is passed." << std::endl;
    std::cout << "Is test passed? " << std::boolalpha << ok << std::endl;

#if ENABLE_LOGGING
    PAUSE();
#endif
}


int main()
{
    Test<ProducerConsumerContextV1>();
    Test<ProducerConsumerContextV2>();
    Test<ProducerConsumerContextV3>();

#ifdef _WIN32
    Test<ProducerConsumerContextWin32<CriticalSection>>();
    Test<ProducerConsumerContextWin32<SRWLock>>();
    Test<ProducerConsumerContextWin32V2>();
#endif

#if FOUND_PTHREADS
    Test<ProducerConsumerContextPThreads>();
#endif

#if !ENABLE_LOGGING
    PAUSE();
#endif

    return 0;
}


// References:
// [0] https://codereview.stackexchange.com/questions/84109/a-multi-threaded-producer-consumer-with-c11
// [1] https://stackoverflow.com/questions/11180134/classical-producer-consumer-threading
// [3] https://stackoverflow.com/questions/10190388/producer-consumer-using-boost-threads-and-circular-buffer-hangs
// [4] https://gist.github.com/Alexis-D/1801206
// [5] http://www.drdobbs.com/a-c-producer-consumer-concurrency-templa/184401751
// [6] https://stackoverflow.com/questions/11706985/win32-thread-safe-queue-implementation-using-native-windows-api
// [7] https://docs.microsoft.com/zh-cn/windows/desktop/Sync/condition-variables
