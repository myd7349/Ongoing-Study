const double mmHgPerPa = 101325.0 / 760.0;
const double mmHgPerkPa = mmHgPerPa / 1000.0;


inline double kPa2mmHg(double kPa)
{
    return kPa / mmHgPerkPa;
}


inline double mmHg2kPa(double mmHg)
{
    return mmHg * mmHgPerkPa;
}


// References:
// https://en.wikipedia.org/wiki/Millimeter_of_mercury

