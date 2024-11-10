/* Modes:
    * 0- reduced testing (2 motors)
    * 1- full testing (6 motors)
    * 2- competition (6 motors)
    * Any other mode will result in compilation error
*/
#define MODE 1

#define PAUSE(x) vexDelay(x);
#define SEC * 1000
#define MSEC
#define CM
#define METER * 100
#define INCH * 2.54

#define RAD
#define DEG * 0.0174532925

// Modes and keybinds
#define brakeMode vex::brakeType::brake
#define intakeKeybind controller.ButtonR1
#define outtakeKeybind controller.ButtonR2
#define pneumaticKeybind controller.ButtonA

vex::brain brain;
vex::controller controller;
#if MODE == 0 // Reduced configuration
vex::motor lm1(vex::PORT1, vex::gearSetting::ratio36_1, false);
vex::motor rm1(vex::PORT2, vex::gearSetting::ratio36_1, true);
AbstractMotorGroup right(&rm1), left(&lm1);
#elif MODE >= 1 and MODE <= 2 // Full configuration
vex::motor rm1(vex::PORT13, vex::ratio6_1, false), rm2(vex::PORT12, vex::ratio6_1, false), rm3(vex::PORT11, vex::ratio6_1, false);
vex::motor lm1(vex::PORT3, vex::ratio6_1, true), lm2(vex::PORT2, vex::ratio6_1, true), lm3(vex::PORT1, vex::ratio6_1, true);
vex::motor intake_hook(vex::PORT14, vex::ratio18_1, false), intake_roller(vex::PORT20, vex::ratio18_1, true);
vex::pneumatics mobile_goal(brain.ThreeWirePort.A);
vex::optical Optical(vex::PORT4);
AbstractMotorGroup right(&rm1, &rm2, &rm3), left(&lm1, &lm2, &lm3);
#endif
BotBase base (
    &left, &right, /* Motor groups */ 
    31.4 /* Base width */,              4.25 /* Wheel radius */,
    12.5 /* Pursuit distance */,        0.052085391069929 /* Gear multiplier */, /*113/99*0.04563233376923-*/
    0.0, 0.0, 0.0 /* Initial pose */,   1 /* Thread sleep: 1 milliseconds */
);
vex::thread t(coordinate_display, (void *) &base);

void autonomous_task();
void control_task();