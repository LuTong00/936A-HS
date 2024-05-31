#include <vex.h>

#include <autonomous/abstractMotorGroup.hpp>
#include <autonomous/odometryDevice.hpp>
#include <autonomous/pid.hpp>
#include <autonomous/purePursuit.hpp>

#include <pathing/matrix.hpp>
#include <pathing/spline.hpp>
#include <pathing/path.hpp>

#include <tests/test_matrix.hpp>
#include <tests/test_odometryDevice.hpp>
#include <tests/test_path.hpp>
#include <tests/test_pid.hpp>
#include <tests/test_purePursuit.hpp>
#include <tests/test_spline.hpp>
#include <tests/virtual_odometryDevice.hpp>

#include <bot.hpp>

#include <bits/stdc++.h>

// Odometry odom(&left, &right, 32.2, 5.1, 0.1186440678, 10);

void f(void* base) {
    BotBase * b = (BotBase *) base;
    b -> follow_path({0, -40, -80, -120, -160, -200}, {0, 10, -10, 10, -10, 10}, 50, 50);
    return;
}

int main() {
    vex::brain brain;
    //vex::controller controller;
    vex::motor l(vex::PORT1, vex::ratio36_1, true), r(vex::PORT2, vex::ratio36_1, false);
    AbstractMotorGroup left(&l), right(&r);
    BotBase base(&left, &right, 32.2, 5.1, 12.5, 0.1186440678, 10);
    brain.Screen.print("Constructed. Following...");
    vex::thread t(f, (void *) &base);
    //base.follow_path({0, -40, -80, -120, -160, -200}, {0, 10, -10, 10, -10, 10}, 50, 50);
    while(1) {
        printf("(%.5f, %.5f)\n", base.odom.x(), base.odom.y());
        vex::this_thread::sleep_for(50);
    }
    left.spin(vex::fwd, 100, vex::pct);
    while(1);
    // BotBase base(&left, &right, 32.2, 5.1, 12.5, 0.1186440678, 10);
    // BotBase b(&left, &right, base_width, wheel_radius, pursuit_distance, gear_multiplier, thread_sleep);
    // base.follow_path({0, -40, -80, -120, -160, -200}, {0, 10, -10, 10, -10, 10}, 50);


    // vex::motor l(vex::PORT1, true), r(vex::PORT2, false);
    // vex::controller controller;
    // AbstractMotorGroup left(&l), right(&r);
    // Odometry odom(&left, &right, 32.2, 5.1, 0.1186440678, 10);
    // int iter = 0;
    // vex::brain brain;
    // std::vector<double> x = {0, -40, -80, -120, -160, -200}, y = {0, 10, -10, 10, -10, 10};
    // Path path(x, y, 50);
    // PurePursuit pursuit(path, 12.5);
    // iter = 0;
    // while (true) {
    //     auto steering = pursuit.get_relative_steering(odom.x(), odom.y(), odom.rotation(), 32.2);
    //     auto target = pursuit.get_target(odom.x(), odom.y());
    //     left.spin(vex::fwd, 0.5 * steering.first, vex::pct);
    //     right.spin(vex::fwd, 0.5 * steering.second, vex::pct);
    //     vex::this_thread::sleep_for(1);
    //     if ((iter++) % 250 == 0) {
    //         brain.Screen.clearScreen();
    //         brain.Screen.setCursor(1, 1);
    //         // printf("Coordinate: (%.5f, %.5f) heading %.5f\n", odom.x(), odom.y(), odom.rotation());
    //         brain.Screen.print("(%.5f, %.5f) heading %.5f", odom.x(), odom.y(), odom.rotation());

    //         brain.Screen.setCursor(2, 1);
    //         // printf("Target: (%.5f, %.5f) (distance = %.5f)\n", target.x, target.y, sqrt((target.x - odom.x()) * (target.x - odom.x()) + (target.y - odom.y()) * (target.y - odom.y())));

    //         brain.Screen.setCursor(3, 1);
    //         // printf("Steering: (%.5f, %.5f)\n", steering.first, steering.second);
    //         brain.Screen.print("(%.5f, %.5f)", steering.first, steering.second);
    //         // printf("\n\n");
    //         printf("(%.5f, %.5f)\n", odom.x(), odom.y());
    //     }
    // }
}