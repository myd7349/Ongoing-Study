#include "nice_label.h"

#include <algorithm>
#include <cmath>


double nice_number(double x, bool round)
{
    int exponent; // exponent of x
    double fraction; // fractional part of x
    double nice_fraction; // nice, rounded fraction

    exponent = std::floor(std::log10(x));
    fraction = x / std::pow(10.0, exponent);

    if (round) {
        if (fraction < 1.5) {
            nice_fraction = 1.0;
        } else if (fraction < 3.0) {
            nice_fraction = 2.0;
        } else if (fraction < 7.0) {
            nice_fraction = 5.0;
        } else {
            nice_fraction = 10.0;
        }
    } else {
        if (fraction <= 1.0) {
            nice_fraction = 1.0;
        } else if (fraction <= 2.0) {
            nice_fraction = 2.0;
        } else if (fraction <= 5.0) {
            nice_fraction = 5.0;
        } else {
            nice_fraction = 10.0;
        }
    }

    return nice_fraction * std::pow(10.0, exponent);
}


// label the data range from rng_min to rng_max loosely.
void loose_label(double rng_min, double rng_max,
                 std::vector<double>::size_type ntick,
                 std::vector<double> &vticks, int &nfrac)
{
    double d; // tick mark spacing

    // graph range min and max
    double graph_min;
    double graph_max;

    double range;

    if (!vticks.empty()) {
        vticks.clear();
    }

    range = nice_number(rng_max - rng_min, false);
    d = nice_number(range / (ntick-1), true);
    graph_min = std::floor(rng_min/d) * d;
    graph_max = std::ceil(rng_max/d) * d;

    // number of fractional digits to show
    nfrac = std::max<int>(-std::floor(std::log10(d)), 0);

    for (double x = graph_min; x <= graph_max + 0.5*d; x += d) {
        // put tick mark at x, with a numerical label
        // showing nfrac fraction digits
        vticks.push_back(x);
    }
}

// References:
// Graphics Gems(Vol.1), Edited by ANDREW S. GLASSNER, 2.2 Nice Numbers for Graph Labels
// https://github.com/erich666/GraphicsGems/blob/master/gems/Label.c
