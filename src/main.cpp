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

void coordinate_display(void* b) {
    BotBase * base = (BotBase *) b;
    printf("[");
    while (true) {
        printf("(%.5f, %.5f, %.5f),\n", base -> odom.x(), base -> odom.y(), base -> odom.rotation());
        vex::this_thread::sleep_for(50);
    }
    return;
}

int main() {
    vex::brain brain;
    vex::controller controller;
    //vex::motor rm1(vex::PORT1, vex::ratio36_1, false), rm2(vex::PORT2, vex::ratio36_1, true), rm3(vex::PORT3, vex::ratio36_1, false);
    //vex::motor lm1(vex::PORT4, vex::ratio36_1, true), lm2(vex::PORT5, vex::ratio36_1, false), lm3(vex::PORT6, vex::ratio36_1, true);
    //AbstractMotorGroup right(&rm1, &rm2, &rm3), left(&lm1, &lm2, &lm3);
    vex::motor l(vex::PORT1, vex::gearSetting::ratio36_1, false);
    vex::motor r(vex::PORT2, vex::gearSetting::ratio36_1, true);
    AbstractMotorGroup left(&l), right(&r);
    BotBase base(&left, &right, 32.2, 5.1, 12.5, 0.1186440678, 10);
    vex::thread t(coordinate_display, (void *) &base);
    vexDelay(1); // DO NOT REMOVE!!! IMPORTANT FOR ODOMETRY TO ZERO
    //base.follow_path({0, -40, -80, -120, -160, -200}, {0, 5, -5, 5, -5, 5}, 5, 0.5, 100);
    base.forward(100, 5.0, 1.0);
    //base.turn(5, 0.02);
    // vexDelay(1000);
    // printf("!\n");
    // base.turn_to(0, 0.02);
    while(true) vexDelay(1000);
}