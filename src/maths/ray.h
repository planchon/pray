#pragma once

#include "vec3.h"

class Ray {
public:
    vec3 direction;
    point3 origin;

    Ray() {}
    Ray(point3 o, vec3 d) : origin(o), direction(d) {}

    point3 at(double t) const {
        return origin + t * direction;
    }
};