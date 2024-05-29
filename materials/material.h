#ifndef MATERIAL_H
#define MATERIAL_H

#include "../common.h"

class HitRecord;

class Material {
public:
    virtual ~Material() = default;

    virtual bool scatter(const Ray& ray, const HitRecord& record, Color& attenuation, Ray& scattered) const {
        return false;
    }
};

#endif //MATERIAL_H
