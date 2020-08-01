#include "FindPeaks.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <numeric>
#include <unordered_set>


// A C++ port of https://github.com/demotu/BMC/blob/master/functions/detect_peaks.py
// https://github.com/demotu/detecta/blob/master/detecta/detect_peaks.py
std::size_t FindPeaks(const double *data, std::size_t length,
    std::deque<std::size_t> &peaks,
    double mph,
    std::size_t mpd,
    double threshold,
    EdgeType edge,
    bool kpsh,
    bool valley)
{
    peaks.clear();

    if (length < 3)
        return 0;

    std::deque<double> x(data, data + length);

    if (valley)
    {
        std::transform(x.cbegin(), x.cend(), x.begin(),
            [](double v) { return -v; });

        if (!std::isnan(mph))
            mph = -mph;
    }

    // dx
    std::deque<double> dx(x.size());
    std::adjacent_difference(x.cbegin(), x.cend(), dx.begin());
    dx.pop_front();

    // Handle NaN's
    std::unordered_set<std::size_t> nans;
    for (std::deque<double>::size_type i = 0; i < x.size(); ++i)
    {
        if (std::isnan(x[i]))
            nans.insert(i);
    }
    //
    if (!nans.empty())
    {
        std::transform(x.cbegin(), x.cend(), x.begin(),
            [](double v) { return std::isnan(v) ? INFINITY : v; });
        std::transform(dx.cbegin(), dx.cend(), dx.begin(),
            [](double v) { return std::isnan(v) ? INFINITY : v; });        
    }

    // Find indices of all peaks

    // Example:
    //   x:       [ 1,  4,  2,  2,  1]
    //   dx:         [ 3, -2,  0, -1]
    // (dx, 0): [ 3, -2,  0, -1,  0]
    // (0, dx):     [ 0,  3, -2,  0, -1]
    for (std::size_t i = 0; i < x.size(); ++i)
    {
        double dxOnLeft = i == x.size() - 1 ? 0 : dx[i];
        double dxOnRight = i == 0 ? 0 : dx[i - 1];

        switch (edge)
        {
        case EdgeNone:
            if (dxOnLeft < 0 && dxOnRight > 0)
                peaks.push_back(i);
            break;
        case EdgeBoth:
            if (dxOnLeft <= 0 && dxOnRight >= 0)
                peaks.push_back(i);
            break;
        case EdgeFalling:
            if (dxOnLeft < 0 && dxOnRight >= 0)
                peaks.push_back(i);
            break;
        case EdgeRising:
            if (dxOnLeft <= 0 && dxOnRight > 0)
                peaks.push_back(i);
            break;
        default:
            assert(false && "Invalid Edge type");
            break;
        }
    }

    std::deque<std::size_t>::iterator last;

    // Handle NaN's
    if (!peaks.empty() && !nans.empty())
    {
        // NaN's and values close to NaN's cannot be peaks
        last = std::remove_if(peaks.begin(), peaks.end(),
            [&nans, &x](std::size_t index)
            {
                return nans.find(index) != nans.cend()
                    || (index > 0 && nans.find(index - 1) != nans.cend())
                    || (index < x.size() - 1 && nans.find(index + 1) != nans.cend());
            });
        peaks.erase(last, peaks.end());
    }

    // First and last values of x cannot be peaks
    if (!peaks.empty() && peaks.front() == 0)
        peaks.pop_front();
    if (!peaks.empty() && peaks.back() == x.size() - 1)
        peaks.pop_back();

    // Remove peaks < minimum peak height
    last = std::remove_if(peaks.begin(), peaks.end(),
        [&x, mph](std::size_t pos){ return x[pos] < mph; });
    peaks.erase(last, peaks.end());

    // Remove peaks - neighbors < threshold
    if (!peaks.empty() && threshold > 0.0)
    {
        last = std::remove_if(peaks.begin(), peaks.end(),
            [&x, threshold](std::size_t index)
            {
                double d = std::min(
                    x[index] - x[index - 1],
                    x[index] - x[index + 1]
                    );
                return d < threshold;
            });
        peaks.erase(last, peaks.end());
    }

    // Detect small peaks closer than minimum peak distance
    if (!peaks.empty() && mpd > 1)
    {
        // Sort peaks by peak height
        std::sort(peaks.begin(), peaks.end(),
            [&x](std::size_t lhs, std::size_t rhs)
            {
                return x[lhs] > x[rhs];
            });

        std::deque<bool> idel(peaks.size());

        for (std::deque<bool>::size_type i = 0; i < idel.size(); ++i)
        {
            if (!idel[i])
            {
                for (std::deque<bool>::size_type j = i + 1; j < idel.size(); ++j)
                {
                    auto minmax = std::minmax(peaks[i], peaks[j]);
                    idel[j] = idel[j] ||
                        ((minmax.second - minmax.first <= mpd) &&
                        // Keep peaks with the same height if kpsh is true
                        (kpsh ? x[peaks[i]] > x[peaks[j]] : true));
                }
            }
        }

        // Remove the small peaks and sort back the indices by their occurrence
        std::size_t index = 0;
        last = std::remove_if(peaks.begin(), peaks.end(),
            [&index, &idel](std::size_t /* pos */) { return idel[index++]; });
        peaks.erase(last, peaks.end());
        std::sort(peaks.begin(), peaks.end());
    }

    return peaks.size();
}


// References:
// MATLAB: findpeaks
// https://stackoverflow.com/questions/1713335/peak-finding-algorithm-for-python-scipy/
// http://nbviewer.jupyter.org/github/demotu/BMC/blob/master/notebooks/DetectPeaks.ipynb
// https://ccrma.stanford.edu/~jos/sasp/Quadratic_Peak_Interpolation.html
// https://github.com/MonsieurV/py-findpeaks
