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

#include <bits/stdc++.h>

// Odometry odom(&left, &right, 32.2, 5.1, 0.1186440678, 10);

#undef print

int main() {
    /*
    To do:
    - Ensure all software tests run smoothly
    - Ensure all classes contain compiler-generated default functions (copy/move construction/assignment)
    - Verify proper documentation
    - Perform hardware tests
        * Odometry
        * AbstractMotorGroup
    */
    // implement driver code
    vex::motor l(vex::PORT1, true), r(vex::PORT2, false);
    vex::controller controller;
    AbstractMotorGroup left(&l), right(&r);
    Odometry odom(&left, &right, 32.2, 5.1, 0.1186440678, 10);
    int iter = 0;
    while (true) {
        double a3, a1;
        a3 = controller.Axis3.position();
        a1 = controller.Axis1.position();
        left.spin(vex::fwd, a3 + a1, vex::pct);
        right.spin(vex::fwd, a3 - a1, vex::pct);
        if (!(iter++ % 1000)) {
            printf("(%.5f, %.5f) heading %.5f\n", odom.x(), odom.y(), odom.rotation());
        }
        vex::this_thread::sleep_for(1);
    }
    // vex::motor l(vex::PORT1, true), r(vex::PORT2, false);
    // vex::brain brain;
    // AbstractMotorGroup left(&l), right(&r);
    // Odometry odom(&left, &right, 32.2, 5.1, 0.1186440678, 10);
    // int iter = 0;
    // // while (true) {
    // //     brain.Screen.clearScreen();
    // //     brain.Screen.setCursor(1, 1);
    // //     printf("(%.5f, %.5f) heading %.5f (iteration %d)\n", odom.x(), odom.y(), odom.rotation(), iter++);
    // //     brain.Screen.print("(%.5f, %.5f) heading %.5f (iteration %d)", odom.x(), odom.y(), odom.rotation(), iter);
    // //     vex::this_thread::sleep_for(1000);
    // // }
    // std::vector<double> x = {0, 10, 20, 30, 40}, y = {0, 25, 100, 225, 400};
    // Path path(x, y, 50);
    // for (auto point : path.points) {
    //     std::cout << "(" << point.x << ", " << point.y << ")" << std::endl;
    // }
    // PurePursuit pursuit(path, 5.0);
    // iter = 0;
    // while (true) {
    //     auto steering = pursuit.get_relative_steering(odom.x(), odom.y(), odom.rotation(), 32.2);
    //     auto target = pursuit.get_target(odom.x(), odom.y());
    //     left.spin(vex::fwd, 0.05 * steering.first, vex::pct);
    //     right.spin(vex::fwd, 0.05 * steering.second, vex::pct);
    //     vex::this_thread::sleep_for(1);
    //     if ((iter++) % 250 == 0) {
    //         brain.Screen.clearScreen();
    //         brain.Screen.setCursor(1, 1);
    //         printf("Coordinate: (%.5f, %.5f) heading %.5f\n", odom.x(), odom.y(), odom.rotation());
    //         brain.Screen.print("(%.5f, %.5f) heading %.5f", odom.x(), odom.y(), odom.rotation());

    //         brain.Screen.setCursor(2, 1);
    //         printf("Target: (%.5f, %.5f) (distance = %.5f)\n", target.x, target.y, sqrt((target.x - odom.x()) * (target.x - odom.x()) + (target.y - odom.y()) * (target.y - odom.y())));
    //         printf("\n\n");

    //         brain.Screen.setCursor(3, 1);
    //         printf("Steering: (%.5f, %.5f)\n", steering.first, steering.second);
    //         brain.Screen.print("(%.5f, %.5f)", steering.first, steering.second);
            
    //     }
    // }
}