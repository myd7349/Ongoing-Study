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
// http://dicom.nema.org/medical/dicom/current/output/html/part16.html#sect_CID_3663
// > BSA = 0.003207*WT^(0.7285-0.0188*log(WT))*HT^0.3
//   BSA = 0.007184*WT^0.425*HT^0.725
//   BSA = 0.0235*WT^0.51456*HTcm^0.42246
//   BSA = 0.024265*WT^0.5378*HTcm^0.3964
//   BSA = (HT*WT/36)^0.5
//   BSA = 1321+0.3433*WT
//   BSA = 0.0004688*WT^(0.8168-0.0154*log(WT))
//   BSA = 0.007358*WT^0.425*HT^0.725
//   BSA = 0.010265*WT^0.423*HT^0.651
//   BSA = 0.008883*WT^0.444*HT^0.663
//   BSA = 0.038189*WT^0.423*HT^0.362
//   BSA = 0.009568*WT^0.473*HT^0.655
