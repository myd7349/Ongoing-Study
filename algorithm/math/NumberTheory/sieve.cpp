// 2018-03-20T14:49+08:00
// A C++11 clone of [0].
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <thread>

#include "../../../cpp/C++11/channel.hpp"
#include "is_prime.h"


const int MAX_SINK_SIZE = 256;


struct Args
{
    std::shared_ptr<Channel> channel;
    int limit;
    int sinkSize;
};


void GenerateOddNumbers(Args &args)
{
    int i = 2;
    std::shared_ptr<Channel> input = args.channel;

    if (input->Send(&i, sizeof i) > 0)
    {
        for (i = 3; input->Send(&i, sizeof i);)
            i += 2;
    }
}


void Filter(int (&primes)[MAX_SINK_SIZE + 1], std::shared_ptr<Channel> input, std::shared_ptr<Channel> output)
{
    int j;
    int x;

    while (true)
    {
        input->Receive(&x, sizeof x);

        // Check if x is a multiple of primes[0...]
        for (j = 0; primes[j] != 0 && x % primes[j] != 0;)
            ++j;

        if (primes[j] == 0)
        {
            if (output->Send(&x, sizeof x) == 0)
                break;
        }
    }

    input->Receive(&x, 0);
}


void Sink(Args &args)
{
    std::shared_ptr<Channel> input = args.channel;
    int i = 0;
    int j;
    int x;
    int primes[MAX_SINK_SIZE + 1];

    primes[0] = 0;

    while (true)
    {
        input->Receive(&x, sizeof x);

        // Check if x is a multiple of primes[0...]
        for (j = 0; primes[j] != 0 && x % primes[j] != 0;)
            ++j;

        if (primes[j] == 0)
        {
            // x is prime
            if (x > args.limit)
                break;

            assert(is_prime(x));
            std::cout << x << ' ';
            primes[i++] = x;
            primes[i] = 0;

            // If sink is full:
            // 1. Call Filter to convert this sink to a filter;
            // 2. Span a new sink;
            if (i == args.sinkSize)
            {
#ifndef NDEBUG
                std::cout << '\n';
#endif

                args.channel = std::make_shared<Channel>();
                std::thread newSinkThrd(Sink, std::ref(args));
                newSinkThrd.detach();
                Filter(primes, input, args.channel);
                return;
            }
        }
    }

    std::cout << '\n';

    input->Receive(&x, 0);
}


int main(int argc, char *argv[])
{
    Args args;
    args.channel = std::make_shared<Channel>();
    args.limit = argc > 1 ? std::atoi(argv[1]) : 1000;
    args.sinkSize = argc > 2 ? std::atoi(argv[2]) : 5;
    if (args.sinkSize > MAX_SINK_SIZE)
        args.sinkSize = MAX_SINK_SIZE;

#ifndef NDEBUG
    std::cout << "---------- Debug Mode On ----------\n";
    std::cout << "Sink Size: " << args.sinkSize << '\n';
    std::cout << "Limit: " << args.limit << '\n';
#endif
    
    std::thread genOddNumsThrd(GenerateOddNumbers, std::ref(args));
    std::thread sinkThrd(Sink, std::ref(args));

    sinkThrd.join();
    genOddNumsThrd.join();

    return 0;
}

// References:
// [0] https://github.com/drh/cii/blob/master/examples/sieve.c
// [1] https://en.wikipedia.org/wiki/Prime_number
// [2] https://en.wikipedia.org/wiki/Generating_primes
// [3] https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
// https://github.com/kimwalisch/primesieve
