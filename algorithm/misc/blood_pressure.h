inline double CalculateMAP(double systolicPressure, double diastolicPressure)
{
    return (2.0 * diastolicPressure + systolicPressure) / 3.0;
}

// References:
// https://en.wikipedia.org/wiki/Blood_pressure
// https://en.wikipedia.org/wiki/Mean_arterial_pressure
