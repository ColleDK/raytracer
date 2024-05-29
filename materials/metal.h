#ifndef METAL_H
#define METAL_H

#include "material.h"
#include "../hittable.h"

class Metal: public Material {
public:
    explicit Metal(const Color& albedo, double fuzz): albedo(albedo), fuzz(fmax(fuzz, 1)) {}

    bool scatter(const Ray &ray, const HitRecord &record, Color &attenuation, Ray &scattered) const override {
        Vec3 reflected = reflect(ray.direction(), record.normal);
        reflected = unitVector(reflected) + (fuzz * randomUnitVector());
        scattered = Ray(record.point, reflected);
        attenuation = albedo;
        return (dotProduct(scattered.direction(), record.normal) > 0);
    }

private:
    Color albedo;
    double fuzz;
};

#endif //METAL_H
