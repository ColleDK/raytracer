#include <iostream>

int main() {

    int imageWidth = 256;
    int imageHeight = 256;

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int i = 0; i < imageHeight; ++i) {
        std::clog << "\rScanlines remaining: " << (imageHeight - i) << ' ' << std::flush;

        for (int j = 0; j < imageWidth; ++j) {
            auto red = double(j) / (imageWidth - 1);
            auto green = double(i) / (imageHeight - 1);
            auto blue = 0.0;

            int ir = int(255.999 * red);
            int ig = int(255.999 * green);
            int ib = int(255.999 * blue);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }

    std::clog << "\rDone.                 \n";
    return 0;
}
