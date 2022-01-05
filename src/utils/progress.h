#pragma once

#include <stdio.h>

class Progress {
public:
    int max, index, one_part;
    int NUMBER_TILD = 100;
    int index_iter = 0;
    char begin = '[';
    char end = ']';
    char middle = '#';
    std::string title;

    Progress(int max, std::string title) {
        max = max;
        title = title;
        one_part = max / 100;
        index = 0;
    }
    
    void update() {
        PROFILE_ME_AS("Progress::update");
        index_iter++;
        if (index_iter > one_part) {
            index++;
            index_iter = 0;
            render();
        }
    }

    void render_finish() {
        std::cout << "rendering finished" << std::endl;     
    }

    void render() {
        printf("\33c\e[3J");
        std::cout << "rendering" << " ";
        printf("%c", begin);
        for (int i = 0; i < NUMBER_TILD; i++) {
            if (i < index) {
                printf("%c", middle);
            } else {
                printf(" ");
            }
        }
        printf("%c %d", end, index);
        printf("\n");
    }
};