#ifndef HITTABLELIST_H
#define HITTABLELIST_H

#include "common.h"
#include <vector>
#include "hittable.h"

class HittableList: public Hittable {

public:
    std::pmr::vector<shared_ptr<Hittable>> objects;

    HittableList() = default;

    explicit HittableList(const shared_ptr<Hittable> &objects) { add(objects); }

    void clear() { objects.clear(); }
    void add(const shared_ptr<Hittable> &object) {
        objects.push_back(object);
    }

    bool hasHit(const Ray &ray, const double tMin, const double tMax, HitRecord &record) const override {
        HitRecord tempRecord;
        bool hitAny = false;
        auto shortestDistance = tMax;

        for (const auto& object: objects) {
            if (object->hasHit(ray, tMin, shortestDistance, tempRecord)) {
                hitAny = true;
                shortestDistance = tempRecord.t;
                record = tempRecord;
            }
        }

        return hitAny;
    }
};

#endif //HITTABLELIST_H
