#ifndef INTERVAL_H
#define INTERVAL_H

#include "common.h"

class Interval {
public:
    double min, max;

    Interval(): min(+infinity), max(-infinity) {}
    Interval(const double min, const double max): min(min), max(max) {}

    [[nodiscard]] double size() const {
        return max - min;
    }

    [[nodiscard]] bool contains(const double value) const {
        return min <= value && max >= value;
    }

    [[nodiscard]] bool surrounds(const double value) const {
        return min < value && max > value;
    }

    [[nodiscard]] double clamp(const double value) const {
        if (value < min) return min;
        if (value > max) return max;
        return value;
    }

    static const Interval empty, universe;
};

const Interval Interval::empty = Interval(+infinity, -infinity);
const Interval Interval::universe = Interval(-infinity, +infinity);

#endif //INTERVAL_H
