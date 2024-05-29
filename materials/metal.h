#ifndef METAL_H
#define METAL_H

#include "material.h"
#include "../hittable.h"

class Metal: public Material {
public:
    explicit Metal(const Color& albedo): albedo(albedo) {}

    bool scatter(const Ray &ray, const HitRecord &record, Color &attenuation, Ray &scattered) const override {
        const Vec3 reflected = reflect(ray.direction(), record.normal);
        scattered = Ray(record.point, reflected);
        attenuation = albedo;
        return true;
    }

private:
    Color albedo;
};

#endif //METAL_H
