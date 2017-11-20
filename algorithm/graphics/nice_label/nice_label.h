// 2014-05-26T17:20+08:00
#ifndef NICE_LABEL_H_
#define NICE_LABEL_H_

#include <vector>

// find a "nice" number approximately equal to x.
// Round the number if round == true, take ceiling if
// round == false.
double nice_number(double x, bool round);

// label the data range from rng_min to rng_max loosely.
void loose_label(double rng_min, double rng_max,
                 std::vector<double>::size_type ntick,
                 std::vector<double> &vticks, int &nfrac);

#endif // NICE_LABEL_H_
