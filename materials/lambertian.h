#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H
#include "material.h"
#include "../hittable.h"

class Lambertian: public Material {
public:
    explicit Lambertian(const Color& albedo): albedo(albedo) {}

    bool scatter(const Ray &ray, const HitRecord &record, Color &attenuation, Ray &scattered) const override {
        auto scatterDirection = record.normal + randomUnitVector();
        if (scatterDirection.nearZero()) {
            scatterDirection = record.normal;
        }
        scattered = Ray(record.point, scatterDirection);
        attenuation = albedo;
        return true;
    }

private:
    Color albedo;
};

#endif //LAMBERTIAN_H
