#ifndef TEST_SPLINE_HPP
#define TEST_SPLINE_HPP

#include <pathing/spline.hpp>
#include <cstdio>

/**
 * @brief Spline tester function.
*/
void test_spline() {
    std::vector<double> x = {3.1, 4.1, 5.9, 2.6, 5.3};
    std::vector<double> y = {5.8, 9.7, 9.3, 2.3, 8.4};
    std::vector<double> p = {1, 2, 3, 4, 5};

    CubicSpline x_spline(p, x);
    CubicSpline y_spline(p, y);

    std::vector<double> interp_p = linspace(0.0, 6.0, 100);

    std::vector<double> interp_x = x_spline(interp_p);
    std::vector<double> interp_y = y_spline(interp_p);

    for (int i = 0; i < interp_x.size(); ++i) {
        printf("(%.5f, %.5f), ", interp_x[i], interp_y[i]);
        if (i % 4 == 3) {
            printf("\n");
        }
    }
    printf("\n");
}

#endif