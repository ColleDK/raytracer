#include <iostream>
#include "color.h"
#include "vec3.h"

int main() {
    constexpr int imageWidth = 256;
    constexpr int imageHeight = 256;

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int i = 0; i < imageHeight; ++i) {
        std::clog << "\rScanlines remaining: " << (imageHeight - i) << ' ' << std::flush;
        for (int j = 0; j < imageWidth; ++j) {
            auto pixelColor = Color(static_cast<double>(j) / (imageWidth - 1), static_cast<double>(i) / (imageHeight - 1), 0);
            writeColor(std::cout, pixelColor);
        }
    }

    std::clog << "\rDone.                 \n";
    return 0;
}
