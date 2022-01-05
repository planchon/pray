#pragma once

#include "../maths/vec3.h"

struct Hit {
    point3 p;
    vec3 normal;
    double t;
    bool front;

    inline void set_face_normal(const Ray &r, const vec3& v) {
        front = dot(r.direction, v) < 0;
        normal = front ? v : -v; 
    }
};