#ifndef COLOR_H
#define COLOR_H
#include "vec3.h"
#include <iostream>

using Color = Vec3;

inline void writeColor(std::ostream& out, const Color& pixelColor) {
    const auto red = pixelColor.x();
    const auto green = pixelColor.y();
    const auto blue = pixelColor.z();

    // Translate the [0,1] component values to the byte range [0,255].
    const int redByte = static_cast<int>(255.999 * red);
    const int greenByte = static_cast<int>(255.999 * green);
    const int blueByte = static_cast<int>(255.999 * blue);

    // Write out the pixel color components.
    out << redByte << ' ' << greenByte << ' ' << blueByte << '\n';
}

#endif //COLOR_H
