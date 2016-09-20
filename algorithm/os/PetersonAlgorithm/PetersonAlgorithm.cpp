#include "PetersonAlgorithm.h"

#include <atomic>
#include <cassert>

namespace {
const int N = 2; // number of processes(workers)
std::atomic_bool flags[N];
std::atomic_int turn;
}

void EnterRegion(int workerId)
{
    assert(workerId == 0 || workerId == 1);

    int theOtherWorkerId = 1 - workerId;
    flags[workerId] = true;
    turn = workerId;

    while (turn == workerId && flags[theOtherWorkerId]) {
        ;
    }
}

void LeaveRegion(int workerId)
{
    assert(workerId == 0 || workerId == 1);

    flags[workerId] = false;
}
