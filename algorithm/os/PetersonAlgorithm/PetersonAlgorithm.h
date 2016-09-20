#ifndef PETERSONALGORITHM_HPP_INCLUDED
#define PETERSONALGORITHM_HPP_INCLUDED

// Peterson's algorithm for 2 processes(workers).

void EnterRegion(int workerId);
void LeaveRegion(int workerId);

#endif // PETERSONALGORITHM_HPP_INCLUDED
