#include "common.h"
#include "shapes/sphere.h"
#include "hittable.h"
#include "camera.h"
#include "hittablelist.h"
#include "materials/lambertian.h"
#include "materials/metal.h"

int main() {
    // World
    HittableList world;

    auto materialGround = make_shared<Lambertian>(Color{0.8, 0.8, 0.0});
    auto materialCenter = make_shared<Lambertian>(Color{0.1, 0.2, 0.5});
    auto materialLeft = make_shared<Metal>(Color{0.8, 0.8, 0.8});
    auto materialRight = make_shared<Metal>(Color{0.8, 0.6, 0.2});

    world.add(make_shared<Sphere>(Vec3( 0.0, -100.5, -1.0), 100.0, materialGround));
    world.add(make_shared<Sphere>(Vec3( 0.0,    0.0, -1.2),   0.5, materialCenter));
    world.add(make_shared<Sphere>(Vec3(-1.0,    0.0, -1.0),   0.5, materialLeft));
    world.add(make_shared<Sphere>(Vec3( 1.0,    0.0, -1.0),   0.5, materialRight));

    Camera camera;

    camera.aspectRatio = 16.0 / 9.0;
    camera.imageWidth = 400;
    camera.samplesPerPixel = 30;
    camera.maxDepth = 10;

    camera.render(world);
    return 0;
}
