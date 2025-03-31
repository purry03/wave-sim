#ifndef RANDOM_H
#define RANDOM_H

#include <cstdlib>

class SmoothRandom {
public:
    SmoothRandom(double min, double max, double smoothFactor = 0.1);
    double getNextValue();

private:
    double minVal, maxVal, smoothFactor, currentValue;
    static double randomInRange(double min, double max);
};

#endif // RANDOM_H
