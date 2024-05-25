#ifndef RAY_H
#define RAY_H
#include "vec3.h"

class Ray {
public:
    // Constructor
    Ray() = default;
    Ray(const Vec3& origin, const Vec3& direction): originPos(origin), dir(direction) {}

    // Utility functions
    [[nodiscard]] const Vec3& origin() const { return originPos; }
    [[nodiscard]] const Vec3& direction() const { return dir; }
    [[nodiscard]] Vec3 at(const double t) const {
        return originPos + t * dir;
    }

private:
    Vec3 originPos;
    Vec3 dir;
};

#endif //RAY_H
