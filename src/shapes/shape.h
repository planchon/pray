#pragma once 

#include "../maths/ray.h"
#include "../maths/vec3.h"
#include "../core/hit.h"
#include <iostream>

class Shape {
public:
    virtual bool intersect(const Ray &r, double tmin, double tmax, Hit &hit) const = 0;
};
