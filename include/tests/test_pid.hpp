#ifndef TEST_PID_HPP
#define TEST_PID_HPP

#include <autonomous/pid.hpp>
#include <cstdio>

void test_pid() {
    PID pid(1.0, 0.005, 0.5, 0.5, 100.0, 0.999);
    pid.set_target(0.0);
    double position = 0.5;
    double delta = 0.0;
    for (int i = 0; i < 100000; ++i) {
        delta = pid.calculate(position) * 0.0001;
        position += delta;
        printf("Old position: %.7f, Change: %.7f, New position: %.7f\n", position - delta, delta, position);
        for (int j = 0; j < 1000000; ++j);
    }
    pid.reset();
}

#endif