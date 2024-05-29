#ifndef SPHERE_H
#define SPHERE_H

#include <utility>

#include "../common.h"
#include "../hittable.h"

class Sphere: public Hittable {
public:
    // Constructors
    Sphere(): centerPos({}), r(0.0) {}
    Sphere(const Vec3& center, const double radius, shared_ptr<Material> material): centerPos(center), r(fmax(0, radius)), material(std::move(material)) {}

    // Hittable functions
    bool hasHit(const Ray &ray, Interval tInterval, HitRecord &record) const override {
        const Vec3 oc = center() - ray.origin();
        const auto a = ray.direction().lengthSquared();
        const auto h = dotProduct(ray.direction(), oc);
        const auto c = oc.lengthSquared() - radius() * radius();

        const auto discriminant = h * h - a * c;
        if (discriminant < 0) {
            return false;
        }

        const auto sqrtd = sqrt(discriminant);

        // Find the nearest node that is within the acceptable range
        auto root = (h - sqrtd) / a;
        if (!tInterval.surrounds(root)) {
            root = (h + sqrtd) / a;
            if (!tInterval.surrounds(root)) {
                return false;
            }
        }

        record.t = root;
        record.point = ray.at(root);
        record.setNormal(ray, (record.point - center()) / radius());
        record.material = material;
        return true;
    }

    //
    [[nodiscard]] const Vec3& center() const { return centerPos; }
    [[nodiscard]] double radius() const { return r; }

private:
    Vec3 centerPos;
    double r;
    shared_ptr<Material> material;
};

#endif //SPHERE_H
