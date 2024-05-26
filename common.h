#ifndef COMMON_H
#define COMMON_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

using std::make_shared;
using std::shared_ptr;
using std::sqrt;

// Constants
const double infinity = std::numeric_limits<double>::infinity();
constexpr double pi = 3.1415926535897932385;

// Utility functions
inline double degreeToRadian(double degrees) {
    return degrees * pi / 180.0;
}

// Common headers
#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "interval.h"

#endif //COMMON_H
