#ifndef BODY_SURFACE_AREA_H_
#define BODY_SURFACE_AREA_H_

#include <cassert>
#include <cmath>


// Calculate body surface area by using Dubois formula
inline double CalcBSA(double hightInCentimeters, double weightInKilograms)
{
    assert(hightInCentimeters > 0.0 && hightInCentimeters < 500.0);
    assert(weightInKilograms > 0.0 && weightInKilograms < 500.0);

    double bodySurfaceAreaInSquareMetre = 
        0.007184 *
        std::pow(weightInKilograms, 0.425) *
        std::pow(hightInCentimeters, 0.725);

    return bodySurfaceAreaInSquareMetre;
}


#endif // BODY_SURFACE_AREA_H_


// References:
// Grossman's Cardiac Catheterization, Angiography, and Intervention, Seventh Edition, Ch8
// https://en.wikipedia.org/wiki/Body_surface_area
