#ifndef FIND_PEAKS_H_
#define FIND_PEAKS_H_

#include <cmath>
#include <cstddef>
#include <deque>


enum EdgeType
{
    EdgeNone,
    EdgeRising,
    EdgeFalling,
    EdgeBoth
};


std::size_t FindPeaks(const double *data, std::size_t length,
    std::deque<std::size_t> &peaks,
    double mph = NAN,
    std::size_t mpd = 1,
    double threshold = 0.0,
    EdgeType edge = EdgeRising,
    bool kpsh = false,
    bool valley = false);

#ifdef __cplusplus
extern "C"
{
#endif

HNALGO_API std::size_t FindPeaks(const double *data, std::size_t length,
    std::size_t *peaks,
    double mph,
    std::size_t mpd = 1,
    double threshold = 0.0,
    EdgeType edge = EdgeRising,
    bool kpsh = false,
    bool valley = false);

#ifdef __cplusplus
}
#endif

#endif // FIND_PEAKS_H_
