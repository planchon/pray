#include <iostream>

#include "../core/camera.h"
#include "../maths/vec3.h"
#include "../core/scene.h"
#include "../shapes/sphere.h"
#include "../utils/profile.h"

#include <chrono>
#include <thread>

int main(int argc, char** argv) {
    PROFILE_ME_AS("pray::main");
    Camera cam = Camera(400, 300, 90.f, vec3(0, 0, 0), 100);
    Scene scene = Scene();

    scene.add(make_shared<Sphere>(vec3(0, 0, -1), 0.5));
    scene.add(make_shared<Sphere>(vec3(0, -100.5, 0), 100));

    cam.render(scene);
    cam.film.dump_to_file("test.ppm");

    PROFILE_END;
    profiler::getInstance().print(std::cout, 60);
}