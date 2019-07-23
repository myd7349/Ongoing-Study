// A C++ port of https://github.com/wfaithfull/cd4soft/blob/master/src/main/java/me/faithfull/cd4soft/cd/CUSUMChangeDetector.java
#ifndef CUSUM_CHANGE_DETECTOR_H_
#define CUSUM_CHANGE_DETECTOR_H_

#include <algorithm>
#include <cmath>

#ifndef NDEBUG
# include <iostream>
#endif


class CUSUMChangeDetector
{
public:
    CUSUMChangeDetector(
        double magnitudeMultiplier = DEFAULT_MAGNITUDE,
        double thresholdMultiplier = DEFAULT_THRESHOLD,
        int readyAfter             = DEFAULT_READY_AFTER)
        : magnitudeMultiplier_(magnitudeMultiplier)
        , thresholdMultiplier_(thresholdMultiplier)
        , readyAfter_(readyAfter)
    {
    }

    bool Update(double xi)
    {
        ++observationCount_;

        // Instead of providing the target mean as a parameter as
        // we would in an offline test, we calculate it as we go to
        // create a target of normality.
        double newMean = runningMean_ + (xi - runningMean_) / observationCount_;
        runningMean_ = newMean;
        runningVariance_ += (xi - runningMean_) * (xi - newMean);

        double std = std::sqrt(runningVariance_);

        magnitude_ = magnitudeMultiplier_ * std;
        threshold_ = thresholdMultiplier_ * std;

        cusum_ = std::max<double>(0.0, cusumPrev_ + (xi - runningMean_ - magnitude_));

        if (IsReady())
            change_ = cusum_ > threshold_;

        cusumPrev_ = cusum_;

        return IsChange();
    }

    bool IsChange() const
    {
        return change_;
    }

    bool IsReady() const
    {
        return observationCount_ >= readyAfter_;
    }

    void Reset()
    {
        observationCount_ = 0;
        runningMean_ = 0.0;
        runningVariance_ = 0.0;

        cusumPrev_ = 0.0;

        change_ = false;
    }

private:
    static constexpr double DEFAULT_MAGNITUDE   = 0.05;
    static constexpr double DEFAULT_THRESHOLD   = 3;
    static constexpr int    DEFAULT_READY_AFTER = 50;

    double magnitudeMultiplier_;
    double thresholdMultiplier_;
    int    readyAfter_;

    int    observationCount_ = 0;
    double runningMean_ = 0.0;
    double runningVariance_ = 0.0;

    double magnitude_;
    double threshold_;

    double cusumPrev_ = 0.0;
    double cusum_;    

    bool change_ = false;
};

#endif // CUSUM_CHANGE_DETECTOR_H_


// References:
// https://dsp.stackexchange.com/questions/30039/detect-to-rising-stable-and-falling-point-in-non-smooth-rectangular-wave
// https://www.mathworks.com/matlabcentral/answers/80743-to-detect-the-edge-of-a-square-wave
// https://www.fs.isy.liu.se/Edu/Courses/TSFS06/PDFs/Basseville.pdf
// https://electronics.stackexchange.com/questions/37055/detecting-phase-between-square-wave-and-sine-wave-signals
// https://faithfull.me/change-detection-for-software-engineers-part-i-introduction-and-cusum/
// https://github.com/wfaithfull/cd4soft
// https://en.wikipedia.org/wiki/Change_detection
// https://www.newton.ac.uk/files/seminar/20140113140015001-153901.pdf
