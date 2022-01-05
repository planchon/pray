#pragma once

#include "../images/image.h"
#include "../core/scene.h"
#include "../shapes/shape.h"
#include "../shapes/sphere.h"
#include "../main/pray.h"
#include "../ext/progress.h"

class Camera {
public:
    vec3 origin, horizontal, vertical, lower_left;
    int width, height, spp;
    double fov, aspect_ratio, viewport_height, viewport_width, focal_length;
    ImagePPM film;

    Camera(int width, int height, double fov, vec3 origin, int spp) {
        this->spp = spp;
        this->width = width;
        this->height = height;
        this->aspect_ratio = double(width) / double(height);
        this->viewport_height = 2.0;
        this->focal_length = 1.0;
        this->viewport_width = aspect_ratio * viewport_height;
        this->fov = fov;
        this->film = ImagePPM(width, height);
        this->origin = origin;
        this->horizontal = vec3(viewport_width, 0, 0);
        this->vertical = vec3(0, viewport_height, 0);
        this->lower_left = origin - horizontal / 2.0 - vertical / 2.0 - vec3(0, 0, focal_length);
    }

    Ray get_ray(double u, double v) {
        return Ray(origin, lower_left + u * horizontal + v * vertical - origin);
    }

    color backgroud_color(Ray& r) {
        vec3 unit_direction = unit_vector(r.direction);
        auto t = 0.5 * (unit_direction.y + 1.0);
        return (1 - t) * color(1, 1, 1) + t * color(0.5, 0.7, 1.0);
    }

    void render(Scene &scene) {
        // progressbar bar(height * width * spp);
        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; i++) {
                color tmp(0, 0, 0);

                for (int sample = 0; sample < spp; sample++) {
                    auto u = double(i + random_double()) / (width - 1);
                    auto v = double(j + random_double()) / (height - 1);

                    Ray r = get_ray(u, v);

                    Hit h;

                    if (scene.intersect(r, 0, 100, h)) {
                        tmp += 0.5 * (h.normal + vec3(1,1,1));
                    } else {
                        tmp += backgroud_color(r);
                    }

                    // bar.update();
                }

                film.set(i, j, tmp / spp);
            }
        }
    }
};