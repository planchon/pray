#pragma once

#include "../maths/ray.h"
#include "../maths/vec3.h"
#include "../core/hit.h"
#include "shape.h"

class Sphere : public Shape {
public:
    double radius;
    vec3 position;

    Sphere() : Shape(), radius(0), position(vec3(0, 0, 0)) {}
    Sphere(vec3 p, double r) : Shape(), radius(r), position(p) {}
    
    virtual bool intersect(const Ray &r, double tmin, double tmax, Hit& hit) const override;
};

bool Sphere::intersect(const Ray &r, double tmin, double tmax, Hit &hit) const {
        vec3 oc = r.origin - position;
        auto a = r.direction.length_square();
        auto half_b = dot(oc, r.direction);
        auto c = oc.length_square() - radius * radius;

        auto disc = half_b * half_b - a * c;
        
        if (disc < 0) {
            return false;
        }

        auto sqrt_disc = std::sqrt(disc);

        auto root = (-half_b - sqrt_disc) / a;

        if (root < tmin || root > tmax) {
            root = (-half_b + sqrt_disc) / a;
            if (root < tmin || root > tmax) {
                return false;
            }
        }

        hit.t = root;
        hit.p = r.at(hit.t);
        vec3 tmp = (hit.p - position) / radius;
        hit.set_face_normal(r, tmp);

        return true;
    }

inline std::ostream& operator<<(std::ostream &out, const Sphere &s) {
    out << "sphere " << s.position << " " << s.radius;
    return out;
}
