#ifndef TEST_ODOMETRY_DEVICE_HPP
#define TEST_ODOMETRY_DEVICE_HPP

#include <autonomous/odometryDevice.hpp>
#include <autonomous/abstractMotorGroup.hpp>
#include <vex.h>
#include <cstdio>

void test_odometryDevice() {
    vex::motor lm1(vex::PORT1), lm2(vex::PORT2), lm3(vex::PORT3);
    vex::motor rm1(vex::PORT4), rm2(vex::PORT5), rm3(vex::PORT6);
    AbstractMotorGroup left(&lm1, &lm2);
    AbstractMotorGroup right(&rm1, &rm2);
    Odometry odom(&left, &right, 30.0, 10.0, 1.0);
    while (true) {
        printf("X: %.5f, Y: %.5f, Theta: %.5f\n", odom.x(), odom.y(), odom.rotation());
    }
}

#endif