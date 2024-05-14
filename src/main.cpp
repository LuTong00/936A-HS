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
    vex::motor l(vex::PORT1, true), r(vex::PORT2, false);
    vex::brain brain;
    AbstractMotorGroup left(&l), right(&r);
    Odometry odom(&left, &right, 32.2, 5.1, 0.1186440678, 10);
    int iter = 0;
    while (true) {
        brain.Screen.clearScreen();
        brain.Screen.setCursor(1, 1);
        printf("(%.5f, %.5f) heading %.5f (iteration %d)\n", odom.x(), odom.y(), odom.rotation(), iter++);
        brain.Screen.print("(%.5f, %.5f) heading %.5f (iteration %d)", odom.x(), odom.y(), odom.rotation(), iter);
        vex::this_thread::sleep_for(1000);
    }
}