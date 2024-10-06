/* Modes:
    * 0- reduced testing (2 motors)
    * 1- full testing (6 motors)
    * 2- competition (6 motors)
    * Any other mode will result in compilation error
*/
#define MODE 0

#define PAUSE(x) vexDelay(x);
#define SEC * 1000
#define MSEC
#define CM
#define METER * 100
#define INCH * 2.54

#define RAD
#define DEG * 0.0174532925


vex::brain brain;
vex::controller controller;
#if MODE == 0 // Reduced configuration
vex::motor lm1(vex::PORT1, vex::gearSetting::ratio36_1, false);
vex::motor rm1(vex::PORT2, vex::gearSetting::ratio36_1, true);
AbstractMotorGroup right(&rm1), left(&lm1);
#elif MODE >= 1 and MODE <= 2 // Full configuration
vex::motor rm1(vex::PORT1, vex::ratio36_1, false), rm2(vex::PORT2, vex::ratio36_1, false), rm3(vex::PORT3, vex::ratio36_1, false);
vex::motor lm1(vex::PORT4, vex::ratio36_1, true), lm2(vex::PORT5, vex::ratio36_1, true), lm3(vex::PORT6, vex::ratio36_1, true);
AbstractMotorGroup right(&rm1, &rm2, &rm3), left(&lm1, &lm2, &lm3);
#endif
BotBase base (
    &left, &right, /* Motor groups */ 
    32.2 /* Base width */,              5.1 /* Wheel radius */,
    12.5 /* Pursuit distance */,        0.1186440678 /* Gear multiplier */,
    0.0, 0.0, 0.0 /* Initial pose */,   1 /* Thread sleep: 1 milliseconds */
);
vex::thread t(coordinate_display, (void *) &base);