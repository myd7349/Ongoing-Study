#include "PrimeFactors.h"


std::list<int> PrimeFactors::Generate(int n)
{
    std::list<int> primes;

    for (int candidate = 2; n > 1; ++candidate) {
        for (; n % candidate == 0; n /= candidate) {
            primes.push_back(candidate);
        }
    }

    return primes;
}