#ifndef DIELECTRIC_H
#define DIELECTRIC_H
#include "material.h"
#include "../hittable.h"

class Dielectric : public Material {
public:
    explicit Dielectric(const double refractionIndex) : refractionIndex(refractionIndex) {}

    bool scatter(const Ray &ray, const HitRecord &record, Color &attenuation, Ray &scattered) const override {
        attenuation = Color{1.0, 1.0, 1.0};
        const double ri = record.isFrontFace ? (1.0 / refractionIndex) : refractionIndex;

        const Vec3 unitDirection = unitVector(ray.direction());

        const double cosTheta = fmin(dotProduct(-unitDirection, record.normal), 1.0);
        const double sinTheta = sqrt(1.0 -cosTheta * cosTheta);
        const bool cannotRefract = ri * sinTheta > 1.0;
        Vec3 refracted;
        if (cannotRefract || reflectance(cosTheta, ri) > randomDouble()) {
            refracted = reflect(unitDirection, record.normal);
        } else {
            refracted = refract(unitDirection, record.normal, ri);
        }

        scattered = Ray(record.point, refracted);
        return true;
    }

private:
    double refractionIndex;

    static double reflectance(const double cos, const double refractionIndex) {
        // Schlicks approximation
        auto r = (1 - refractionIndex) / (1 + refractionIndex);
        r = r * r;
        return r + (1 - r) * pow(1 - cos, 5);
    }
};

#endif //DIELECTRIC_H
