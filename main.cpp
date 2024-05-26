#include "common.h"
#include "shapes/sphere.h"
#include "hittable.h"
#include "camera.h"
#include "hittablelist.h"

int main() {
    // World
    HittableList world;
    world.add(make_shared<Sphere>(Vec3(0, 0, -1), 0.5));
    world.add(make_shared<Sphere>(Vec3(0, -100.5, -1), 100));

    Camera camera;

    camera.aspectRatio = 16.0 / 9.0;
    camera.imageWidth = 400;
    camera.samplesPerPixel = 10;

    camera.render(world);
    return 0;
}
