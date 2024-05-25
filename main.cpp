#include <iostream>
#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "shapes/sphere.h"

double hitSphere(const Sphere& sphere, const Ray& ray) {
    const Vec3 oc = sphere.center() - ray.origin();
    const auto a = ray.direction().lengthSquared();
    const auto h = dotProduct(ray.direction(), oc);
    const auto c = oc.lengthSquared() - sphere.radius() * sphere.radius();

    const auto discriminant = h * h - a * c;
    if (discriminant < 0) {
        return -1.0;
    }
    return (h - sqrt(discriminant)) / a;
}

Color rayColor(const Sphere& sphere, const Ray& ray) {
    if (const auto t = hitSphere(sphere, ray); t > 0.0) {
        auto normal = unitVector(ray.at(t) - Vec3(0, 0, -1));
        normal += Vec3(1.0, 1.0, 1.0);
        return 0.5 * normal;
    }
    const auto blue = Vec3(0.5, 0.7, 1.0);
    const auto white = Vec3(1.0, 1.0, 1.0);

    const auto unitDirection = unitVector(ray.direction());
    const auto a = 0.5 * (unitDirection.y() + 1.0);
    return (1.0 - a) * white + a * blue;
}

int main() {
    // Image sphere
    const auto sphere = Sphere({0, 0, -1}, 0.5);

    // Get the image size
    constexpr auto aspectRatio = 16.0 / 9.0;
    constexpr int imageWidth = 400;
    constexpr int imageHeight =static_cast<int>(imageWidth / aspectRatio);

    // Camera
    constexpr auto focalLength = 1.0;
    constexpr auto viewportHeight = 2.0;
    constexpr auto viewportWidth = viewportHeight * (static_cast<double>(imageWidth) / imageHeight);
    const auto cameraCenter = Vec3();

    // Viewport vectors
    const auto viewportU = Vec3(viewportWidth, 0, 0);
    const auto viewportV = Vec3(0, -viewportHeight, 0);

    // Pixel vectors
    const auto pixelU = viewportU / imageWidth;
    const auto pixelV = viewportV / imageHeight;

    // Get upper left pixel
    const auto viewportUpperLeft = cameraCenter - Vec3(0, 0, focalLength) - viewportU / 2 - viewportV / 2;
    const auto pixelLocation = viewportUpperLeft + 0.5 * (pixelU + pixelV);

    // Rendering
    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";
    for (int i = 0; i < imageHeight; ++i) {
        std::clog << "\rScanlines remaining: " << (imageHeight - i) << ' ' << std::flush;
        for (int j = 0; j < imageWidth; ++j) {
            //auto pixelColor = Color(static_cast<double>(j) / (imageWidth - 1), static_cast<double>(i) / (imageHeight - 1), 0);
            auto pixelCenter = pixelLocation + (j * pixelU) + (i * pixelV);
            auto rayDirection = pixelCenter - cameraCenter;
            Ray ray(cameraCenter, rayDirection);

            auto pixelColor = rayColor(sphere, ray);
            writeColor(std::cout, pixelColor);
        }
    }
    std::clog << "\rDone.                 \n";
    return 0;
}
