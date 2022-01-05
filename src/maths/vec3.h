#pragma once

#include <cmath>
#include <iostream>

class vec3 {
public:
    double x, y, z;

    vec3(): x(0), y(0), z(0) {}
    vec3(double x, double y, double z): x(x), y(y), z(z) {}

    vec3 operator-() const {return vec3(-x, -y, -z);}

    vec3& operator+=(const vec3& vec) {
        x += vec.x;
        y += vec.y;
        z += vec.z;
        return *this;
    }

    vec3& operator*=(const double t) {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }

    vec3& operator/=(const double t) {
        return *this *= 1 / t;
    }

    double length() const {
        return std::sqrt(length_square());
    }

    double length_square() const {
        return x * x + y * y + z * z;
    }

    void print_ppm(std::ostream &out) {
        double max = 255.999;
        out << static_cast<int>(max * x) << " "
            << static_cast<int>(max * y) << " "
            << static_cast<int>(max * z) << "\n";
    }
};

using point3 = vec3;
using color = vec3;

inline std::ostream& operator<<(std::ostream &out, const vec3 &v) {
    out << v.x << " " << v.y << " " << v.z;
    return out;
}

inline vec3 operator+(const vec3 &v, const vec3& u) {
    return vec3(v.x + u.x, v.y + u.y, v.z + u.z);
}

inline vec3 operator-(const vec3 &v, const vec3& u) {
    return vec3(v.x - u.x, v.y - u.y, v.z - u.z);
}

inline vec3 operator*(const vec3 &v, const vec3& u) {
    return vec3(v.x * u.x, v.y * u.y, v.z * u.z);
}

inline vec3 operator*(const double &t, const vec3 &v) {
    return vec3(v.x * t, v.y * t, v.z * t);
}

inline vec3 operator*(const vec3 &v, const double &t) {
    return vec3(v.x * t, v.y * t, v.z * t);
}

inline vec3 operator/(vec3 v, double t) {
    return (1/t) * v;
}

inline double dot(const vec3 &u, const vec3 &v) {
    return u.x * v.x
         + u.y * v.y
         + u.z * v.z;
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(u.y * v.z - u.z * v.y,
                u.z * v.x - u.x * v.z,
                u.x * v.y - u.y * v.x);
}

inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}