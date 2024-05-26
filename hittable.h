#ifndef HITTABLE_H
#define HITTABLE_H
#include "common.h"

class HitRecord {
public:
    Vec3 point{};
    Vec3 normal{};
    double t{};
    bool isFrontFace{};

    void setNormal(const Ray& ray, const Vec3& outwardNormal) {
        isFrontFace = dotProduct(ray.direction(), outwardNormal) < 0;
        normal = isFrontFace ? outwardNormal : -outwardNormal;
    }
};

class Hittable {
public:
    virtual ~Hittable() = default;

    [[nodiscard]] virtual bool hasHit(const Ray& ray, double tMin, double tMax, HitRecord& record) const = 0;
};

#endif //HITTABLE_H
