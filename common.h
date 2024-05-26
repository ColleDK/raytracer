#ifndef COMMON_H
#define COMMON_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <random>

using std::make_shared;
using std::shared_ptr;
using std::sqrt;

// Constants
const double infinity = std::numeric_limits<double>::infinity();
constexpr double pi = 3.1415926535897932385;

// Utility functions
inline double degreeToRadian(const double degrees) {
    return degrees * pi / 180.0;
}

inline double randomDouble() {
    std::random_device rand;
    std::seed_seq seed { rand(), rand(), rand(), rand(), rand(), rand(), rand(), rand() };
    std::mt19937 generator{ seed };

    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(generator);
}

inline double randomDouble(const double min, const double max) {
    return min + (max - min) * randomDouble();
}


// Common headers
#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "interval.h"

#endif //COMMON_H
