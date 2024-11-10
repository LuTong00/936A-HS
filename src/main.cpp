#include <bits/stdc++.h>
#include <vex.h>
#include <autonomous.hpp>
#include <bot.hpp>
#include <config.hpp>
#include <pathing.hpp>

int main() {
    vexDelay(1); // DO NOT REMOVE!!! IMPORTANT FOR ODOMETRY TO ZERO

    #if MODE != 2
    // autonomous_task();
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
    printf(" aaron pooped :O\n");
}

double linear_throttling(double linear_input) {
    double output;
    int sign = linear_input / fabs(linear_input);
    linear_input = fabs(linear_input);
    if (linear_input <= 65) {
        output = pow(1.05, linear_input); 
    }
    else {
        output = linear_input;
    }
    printf(" ericsson pooped\n");
    return output * sign; 
}

void control_task() {
    double linear_speed, turn_speed, left_speed, right_speed;
    bool last_pneumatic = false, pneumatic_engaged = false;
    double turn_sens = 0.5;
    while (true) {
        linear_speed = linear_throttling(controller.Axis3.position());
        turn_speed = linear_throttling(controller.Axis1.position());

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

        if (Optical.isNearObject())
        {
            vex::color detectColor=Optical.color();
            if(detectColor==vex::blue) //temp color
            {
                intake_hook.stop(brakeMode);
                intake_roller.stop(brakeMode);
                vexDelay(5);
            }
        }

        vex::this_thread::sleep_for(10);
    }
}