#ifndef TEST_PURE_PURSUIT_HPP
#define TEST_PURE_PURSUIT_HPP

#include <autonomous/purePursuit.hpp>
#include <cstdio>

void test_purePursuit() {
    std::vector<double> x = {3.1, 4.1, 5.9, 2.6, 5.3};
    std::vector<double> y = {5.8, 9.7, 9.3, 2.3, 8.4};
    Path path(x, y, 100);
    PurePursuit pursuit(path, 0.5);
    Point target = pursuit.get_target(3.0, 5.9);
    for (int i = 0; i < path.points.size(); ++i) {
        printf("(%.5f, %.5f)", path.points[i].x, path.points[i].y);
        if (i != path.points.size() - 1) {
            printf(", ");
        }
        if (i % 4 == 3) {
            printf("\n");
        }
    }
    printf("\n\n");
    printf("Target: (%.5f, %.5f)\n", target.x, target.y);
    std::pair<double, double> steering = pursuit.get_relative_steering(3.0, 5.9, 3.1415 / 2, 0.5);
    printf("Steering power: (%.5f, %.5f)\n", steering.first, steering.second);
    // printf("Distance to target: %.5f\n", pursuit.distance_to_end(3.0, 6.4));
}

#endif