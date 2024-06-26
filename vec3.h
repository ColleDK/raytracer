#ifndef VEC3_H
#define VEC3_H

#include "common.h"

class Vec3 {
public:
    // Coordinates of 3D vector
    double coords[3];

    // Constructors
    Vec3() : coords{0, 0, 0} {}
    Vec3(const double x, const double y, const double z) : coords{x, y, z} {}

    // Retrieve coordinates
    [[nodiscard]] double x() const { return coords[0]; }
    [[nodiscard]] double y() const { return coords[1]; }
    [[nodiscard]] double z() const { return coords[2]; }

    // Operator functions
    Vec3 operator-() const { return {-x(), -y(), -z()}; }
    double operator[](const int index) const { return coords[index]; }
    double& operator[](const int index) { return coords[index]; }
    Vec3& operator+=(const Vec3& other) {
        coords[0] += other.x();
        coords[1] += other.y();
        coords[2] += other.z();
        return *this;
    }
    Vec3& operator-=(const Vec3& other) {
        coords[0] -= other.x();
        coords[1] -= other.y();
        coords[2] -= other.z();
        return *this;
    }
    Vec3& operator/=(const Vec3& other) {
        coords[0] /= other.x();
        coords[1] /= other.y();
        coords[2] /= other.z();
        return *this;
    }
    Vec3& operator*=(const Vec3& other) {
        coords[0] *= other.x();
        coords[1] *= other.y();
        coords[2] *= other.z();
        return *this;
    }

    // Utility functions
    [[nodiscard]] double length() const {
        return sqrt(lengthSquared());
    }

    [[nodiscard]] double lengthSquared() const {
        return x() * x() + y() * y() + z() * z();
    }

    [[nodiscard]] bool nearZero() const {
        constexpr auto s = 1e-8;
        return fabs(x()) < s && fabs(y()) < s && fabs(z()) < s;
    }

    static Vec3 random() {
        return {randomDouble(), randomDouble(), randomDouble()};
    }

    static Vec3 random(const int min, const int max) {
        return {randomDouble(min, max), randomDouble(min, max), randomDouble(min, max)};
    }

};

// Additional utility functions
// Operator functions
inline std::ostream& operator<<(std::ostream& out, const Vec3& vec) {
    return out << vec.x() << ' ' << vec.y() << ' ' << vec.z();
}

inline Vec3 operator+(const Vec3& vec, const Vec3& vec2) {
    return {vec.x() + vec2.x(), vec.y() + vec2.y(), vec.z() + vec2.z()};
}

inline Vec3 operator-(const Vec3& vec1, const Vec3& vec2) {
    return {vec1.x() - vec2.x(), vec1.y() - vec2.y(), vec1.z() - vec2.z()};
}

inline Vec3 operator*(const Vec3& vec1, const Vec3& vec2) {
    return {vec1.x() * vec2.x(), vec1.y() * vec2.y(), vec1.z() * vec2.z()};
}

inline Vec3 operator*(const Vec3& vec, const double t) {
    return {vec.x() * t, vec.y() * t, vec.z() * t};
}

inline Vec3 operator*(const double t, const Vec3& vec) {
    return {vec.x() * t, vec.y() * t, vec.z() * t};
}

inline Vec3 operator/(const Vec3& vec, const double t) {
    return vec * (1/t);
}

// Vector specific functions
inline double dotProduct(const Vec3& vec1,const Vec3& vec2) {
    return vec1.x() * vec2.x() + vec1.y() * vec2.y() + vec1.z() * vec2.z();
}

inline Vec3 crossProduct(const Vec3& vec1,const Vec3& vec2) {
    return {
        vec1.y() * vec2.z() - vec1.z() * vec2.y(),
            vec1.z() * vec2.x() - vec1.x() * vec2.z(),
            vec1.x() * vec2.y() - vec1.y() * vec2.x()
    };
}

inline Vec3 unitVector(const Vec3& vec) {
    return vec / vec.length();
}

inline Vec3 randomInUnitSphere() {
    while (true) {
        if (auto point = Vec3::random(-1, 1); point.lengthSquared() < 1) {
            return point;
        }
    }
}

inline Vec3 randomUnitVector() {
    return unitVector(randomInUnitSphere());
}

inline Vec3 randomOnHemisphere(const Vec3& normal) {
    const Vec3 onUnitSphere = randomUnitVector();
    if (dotProduct(onUnitSphere, normal) > 0.0) {
        return onUnitSphere;
    }
    return -onUnitSphere;
}

inline Vec3 reflect(const Vec3& v, const Vec3& n) {
    return v - 2 * dotProduct(v, n) * n;
}

inline Vec3 refract(const Vec3& v, const Vec3& n, const double eta) {
    const auto cosTheta = fmin(dotProduct(-v, n), 1.0);
    const Vec3 rPerp = eta * (v + cosTheta * n);
    const Vec3 rParallel = -sqrt(fabs(1.0 - rPerp.lengthSquared())) * n;
    return rPerp + rParallel;
}

#endif //VEC3_H
