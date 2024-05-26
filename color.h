#ifndef COLOR_H
#define COLOR_H
#include "vec3.h"
#include "common.h"
#include "interval.h"

using Color = Vec3;

inline void writeColor(std::ostream& out, const Color& pixelColor) {
    const auto red = pixelColor.x();
    const auto green = pixelColor.y();
    const auto blue = pixelColor.z();

    // Translate the [0,1] component values to the byte range [0,255].
    static const Interval intensity(0.000, 0.999);
    const int redByte = static_cast<int>(256 * intensity.clamp(red));
    const int greenByte = static_cast<int>(256 * intensity.clamp(green));
    const int blueByte = static_cast<int>(256 * intensity.clamp(blue));

    // Write out the pixel color components.
    out << redByte << ' ' << greenByte << ' ' << blueByte << '\n';
}

#endif //COLOR_H
