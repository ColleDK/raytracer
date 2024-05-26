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

#endif //VEC3_H
