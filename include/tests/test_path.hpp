#ifndef TEST_PATH_HPP
#define TEST_PATH_HPP

#include <pathing/path.hpp>
#include <cstdio>

void test_path() {
    std::vector<double> x = {3.1, 4.1, 5.9, 2.6, 5.3};
    std::vector<double> y = {5.8, 9.7, 9.3, 2.3, 8.4};
    Path p(x, y, 100);

    for (int i = 0; i < p.points.size(); ++i) {
        printf("(%.5f, %.5f), ", p.points[i].x, p.points[i].y);
        if (i % 4 == 3) {
            printf("\n");
        }
    }
    printf("\n");
}

#endif