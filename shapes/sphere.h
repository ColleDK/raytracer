#ifndef SPHERE_H
#define SPHERE_H

#include "../vec3.h"

class Sphere {
public:
    // Constructors
    Sphere(): centerPos({}), r(0.0) {}
    Sphere(const Vec3& center, const double radius): centerPos(center), r(radius) {}

    //
    [[nodiscard]] const Vec3& center() const { return centerPos; }
    [[nodiscard]] double radius() const { return r; }

private:
    Vec3 centerPos;
    double r;
};

#endif //SPHERE_H
