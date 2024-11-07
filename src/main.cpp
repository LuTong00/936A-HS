#include <iostream>
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
    control_task();
    #else
    vex::competition competition;
    competition.autonomous(autonomous_task);
    competition.drivercontrol(control_task);
    #endif

    while(true) vexDelay(1000); // DO NOT REMOVE!!! IMPORTANT TO KEEP THREADS ALIVE
}

void autonomous_task() {
    //base.follow_path({0, 60, 30, 0}, {0, 30, 60, 30}, 0.5, 0.15);
    /*
    (0, 0)
    (100, 0)
    (100, 100)
    */
    base.follow_path({0, 50, 50}, {0, 0, 50}, 0.5, 0.35);
    //vexDelay(200 MSEC);
    //base.turn_to(90 DEG, 2.5 DEG);
    //vexDelay(2 SEC);
    //base.forward(35, 1.0, 0.1);
    //base.turn_to(450 DEG, 2.5 DEG, 0.25);
}

void control_task() {
    double linear_speed, turn_speed, left_speed, right_speed;
    bool last_pneumatic = false, pneumatic_engaged = false;
    while (true) {
        linear_speed = controller.Axis3.position();
        turn_speed = controller.Axis1.position();
        left_speed = linear_speed + turn_speed;
        right_speed = linear_speed - turn_speed;
        if (fabs(left_speed) > 0.5) {
            left.spin(vex::fwd, left_speed, vex::pct);
        } else {
            left.stop(brakeMode);
        }
        if (fabs(right_speed) > 0.5) {
            right.spin(vex::fwd, right_speed, vex::pct);
        } else {
            right.stop(brakeMode);
        }
        if (intakeKeybind.pressing()) {
            intake_hook.spin(vex::fwd, 100, vex::pct);
            intake_roller.spin(vex::fwd, 100, vex::pct);
        } else if (outtakeKeybind.pressing()) {
            intake_hook.spin(vex::reverse, 100, vex::pct);
            intake_roller.spin(vex::reverse, 100, vex::pct);
        } else {
            intake_hook.stop(brakeMode);
            intake_roller.stop(brakeMode);
        }
        if (pneumaticKeybind.pressing() != last_pneumatic and last_pneumatic == false) {
            if (pneumatic_engaged) {
                mobile_goal.close();
            } else {
                mobile_goal.open();
            }
            pneumatic_engaged = not pneumatic_engaged;
        }
        last_pneumatic = pneumaticKeybind.pressing();
        vex::this_thread::sleep_for(10);
    }
}