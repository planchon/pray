#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include "../maths/vec3.h"
#include "../maths/ray.h"
#include "../utils/profile.h"

class ImagePPM {
public:
    int width, height, channels;
    std::vector<color> data;

    ImagePPM() {};

    ImagePPM(int width, int height) : width(width), height(height), channels(3) {
        data.reserve(width * height);

        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; ++i) {
                auto r = double(i) / (width - 1);
                auto g = double(j) / (height - 1);
                auto b = 0.25;

                set(i, j, r, g, b);
            }
        }
    }

    void set(int x, int y, color pix) {
        int index = x + y * width;
        data[index] = pix;
    }

    void set(int x, int y, double r, double g, double b) {
        color pix(r, g, b);
        int index = x + y * width;
        data[index] = pix;
    }

    inline void dump_to_file(std::string filename) {
        PROFILE_ME_AS("Dumping file");
        std::ofstream file;
        file.open(filename);

        if (!file.is_open()) {
            std::cout << "error while opening image file" << std::endl;
        }

        file << "P3\n" << width << " " << height << "\n255\n";
        
        int index = 0;
        for (int j = height - 1; j >= 0; j--) {
            for (int i = 0; i < width; i++) {
                index = (i + j * width);
                data[index].print_ppm(file);
            }
        }

        file.close();
    }
};