#ifndef CAMERA_H
#define CAMERA_H

#include "common.h"
#include "hittable.h"

class Camera {

public:
    double aspectRatio = 16.0 / 9.0;
    int imageWidth = 400;
    int samplesPerPixel = 10;
    int maxDepth = 10;

    void render(const Hittable& world) {
        initialize();

        std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";
        for (int i = 0; i < imageHeight; ++i) {
            std::clog << "\rScanlines remaining: " << (imageHeight - i) << ' ' << std::flush;
            for (int j = 0; j < imageWidth; ++j) {
                Color pixelColor {};
                for (int sample = 0; sample < samplesPerPixel; sample++) {
                    Ray ray = getRay(j, i);
                    pixelColor += rayColor(ray, maxDepth, world);
                }
                writeColor(std::cout, pixelSampleScale * pixelColor);
            }
        }
        std::clog << "\rDone.\n";
    }

private:
    double pixelSampleScale = 0;
    int imageHeight = 0;
    Vec3 cameraCenter {};
    Vec3 pixelLocation {};
    Vec3 pixelU {};
    Vec3 pixelV {};

    void initialize() {
        imageHeight = static_cast<int>(imageWidth / aspectRatio);
        cameraCenter = {};

        pixelSampleScale = 1.0 / samplesPerPixel;

        constexpr auto focalLength = 1.0;
        constexpr auto viewportHeight = 2.0;
        const auto viewportWidth = viewportHeight * (static_cast<double>(imageWidth) / imageHeight);

        const auto viewportU = Vec3(viewportWidth, 0, 0);
        const auto viewportV = Vec3(0, -viewportHeight, 0);

        pixelU = viewportU / imageWidth;
        pixelV = viewportV / imageHeight;

        const auto viewportUpperLeft = cameraCenter - Vec3(0, 0, focalLength) - viewportU / 2 - viewportV / 2;
        pixelLocation = viewportUpperLeft + 0.5 * (pixelU + pixelV);
    }

    [[nodiscard]] Ray getRay(const int width, const int height) const {
        const auto offset = sampleSquare();
        const auto pixelSample = pixelLocation + ((width + offset.x()) * pixelU) + ((height + offset.y()) * pixelV);

        auto rayOrigin = cameraCenter;
        auto rayDirection = pixelSample - rayOrigin;

        return {rayOrigin, rayDirection};
    }

    [[nodiscard]] static Vec3 sampleSquare() {
        return {randomDouble() - 0.5, randomDouble() - 0.5, 0};
    }

    [[nodiscard]] static Color rayColor(const Ray& ray, const int depth, const Hittable& world) {
        const auto blue = Vec3(0.5, 0.7, 1.0);
        const auto white = Vec3(1.0, 1.0, 1.0);
        const auto black = Vec3(0.0, 0.0, 0.0);

        if (depth <= 0) {
            return black;
        }

        HitRecord record{};
        if (world.hasHit(ray, Interval(0.001, infinity), record)) {
            auto direction = record.normal + randomUnitVector();
            return 0.5 * rayColor({record.point, direction}, depth - 1, world);
        }

        const auto unitDirection = unitVector(ray.direction());
        const auto a = 0.5 * (unitDirection.y() + 1.0);
        return (1.0 - a) * white + a * blue;
    }
};

#endif //CAMERA_H
