const double mmHgPerPa = 101325.0 / 760.0;


inline double kPa2mmHg(double kPa)
{
    return kPa * 1000.0 / mmHgPerPa;
}


inline double mmHg2kPa(double mmHg)
{
    return mmHg * mmHgPerPa / 1000.0;
}


// References:
// https://en.wikipedia.org/wiki/Millimeter_of_mercury

