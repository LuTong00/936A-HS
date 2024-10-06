#include <bits/stdc++.h>
#include <vex.h>
#include <autonomous.hpp>
#include <bot.hpp>
#include <config.hpp>
#include <pathing.hpp>

void autonomous_task() {
    base.follow_path({0, 100, 50, 0}, {0, 50, 100, 50}, 0.5);
    vexDelay(200 MSEC);
    base.turn_to(90 DEG, 2.5 DEG);
    vexDelay(200 MSEC);
    base.forward(100);
    base.turn(90 DEG, 2.5 DEG);
}

void control_task() {
    std::map<std::string, std::function<void()>> keybinds = {
        {} // e.g. {"A+B", [] () {base.forward(100);}}
    };
    double linear_speed = 0, turn_speed = 0;
    while (true) {
        linear_speed = controller.Axis3.position();
        turn_speed = controller.Axis1.position();
        left.spin(vex::fwd, linear_speed + turn_speed, vex::pct);
        right.spin(vex::fwd, linear_speed - turn_speed, vex::pct);
        vex::this_thread::sleep_for(10);
    }
}

int main() {
    vexDelay(1); // DO NOT REMOVE!!! IMPORTANT FOR ODOMETRY TO ZERO

    #if MODE != 2
    autonomous_task();
    //control_task();
    #else
    vex::competition competition;
    competition.autonomous(autonomous_task);
    competition.drivercontrol(control_task);
    #endif

    while(true) vexDelay(1000); // DO NOT REMOVE!!! IMPORTANT TO KEEP THREADS ALIVE
}