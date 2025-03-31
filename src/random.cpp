#include "../include/random.h"
#include <ctime>

// Constructor: Initializes the random number generator and sets the starting value
SmoothRandom::SmoothRandom(double min, double max, double smoothFactor)
    : minVal(min), maxVal(max), smoothFactor(smoothFactor), currentValue(randomInRange(min, max))
{
    srand(time(nullptr));  // Seed the random generator once
}

// Generates a smoothly transitioning random value
double SmoothRandom::getNextValue() {
    double target = randomInRange(minVal, maxVal);  // Generate a new target value
    currentValue += smoothFactor * (target - currentValue);  // Smoothly approach target
    return currentValue;
}

// Generates a random number in the given range
double SmoothRandom::randomInRange(double min, double max) {
    return min + (rand() / (RAND_MAX + 1.0)) * (max - min);
}
