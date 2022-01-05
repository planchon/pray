#pragma once

#include <vector>
#include <memory>
#include "../shapes/shape.h"
#include "../core/hit.h"

using std::shared_ptr;
using std::make_shared;

class Scene : public Shape {
public:
    std::vector<shared_ptr<Shape>> shapes;

    Scene() {}
    Scene(shared_ptr<Shape> obj) { add(obj); }

    void add(shared_ptr<Shape> s) {
        shapes.push_back(s);
    }

    virtual bool intersect(const Ray &r, double tmin, double tmax, Hit &hit) const override;
};

bool Scene::intersect(const Ray &r, double tmin, double tmax, Hit &hit) const {
    Hit tmp_hit;
    bool has_hit = false;
    auto closest = tmax;

    for (const auto& object : shapes) {
        if (object->intersect(r, tmin, closest, tmp_hit)) {
            has_hit = true;
            closest = tmp_hit.t;
            hit = tmp_hit;
        }
    }

    return has_hit;
}