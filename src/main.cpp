#include <iostream>
#include <vex.h>
#include <autonomous.hpp>
#include <bot.hpp>
#include <config.hpp>
#include <pathing.hpp>

controller controller1=controller(primary);

//intake
motor MotorI1 = motor(PORT1, ratio6_1, true); //ports and names temp
motor MotorI2 = motor(PORT1, ratio6_1, false); //ports and names temp

pneumatic Pnuematic = pneumatic(PORT1, false); //port temp
bool pumpstate=false;

optical Optical = optical(PORT1); //port temp
color detectColor=Optical.color();

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

        Controller.ButtonA.pressed(buttonPressed);
        MotorI1.spin(forward);
        MotorI2.spin(reverse); //if it's set to reverse in the definition does it need to be reverse here too?? or is it like double negatives
        if (Optical.isNearObject())
        {
            detectColor=Optical.color();
            if(detectColor==blue) //temp color
            {
                MotorI1.stop();
                MotorI2.stop();
                vexDelay(5);
            }
        }
        
        vex::this_thread::sleep_for(10);
    }
}

void buttonPressed()
{
    if(pumpstate)
    {
        Pneumatic.pumpOff();
        pumpstate=false;
    }
    else 
    {
        Pneumatic.pumpOn();
        pumpstate=true;
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