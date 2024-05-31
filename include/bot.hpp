#ifndef BOT_HPP
#define BOT_HPP

#include <vex.h>
#include <autonomous/abstractMotorGroup.hpp>
#include <autonomous/odometryDevice.hpp>
#include <autonomous/purePursuit.hpp>
#include <pathing/path.hpp>
#include <initializer_list>

class BotBase {
public:
    /**
     * @brief The left motor group
    */
    AbstractMotorGroup* left;

    /**
     * @brief The right motor group
    */
    AbstractMotorGroup* right;

    /**
     * @brief The odometry device to track position
    */
    Odometry odom;

    /**
     * @brief The width of the robot
    */
    double base_width;

    /**
     * @brief The radius of the wheel
    */
    double wheel_radius;

    /**
     * @brief The look-ahead distance
    */
    double pursuit_distance;

    /**
     * @brief The gear multiplier
    */
    double gear_multiplier;
    
    /**
     * @brief The sleep time for the tracking thread, in microseconds
    */
    int thread_sleep;

    /**
     * @brief Construct a new BotBase object
     * @param left The left motor group
     * @param right The right motor group
     * @param base_width The width of the robot
     * @param wheel_radius The radius of the wheel
     * @param pursuit_distance The look-ahead distance
     * @param gear_multiplier The gear multiplier
     * @param thread_sleep The sleep time for the tracking thread, in microseconds
     * @attention Ensure that the distance measurements are in consistent units as odometry.
    */
    BotBase(AbstractMotorGroup* left, AbstractMotorGroup* right, double base_width, double wheel_radius, double pursuit_distance, double gear_multiplier, int thread_sleep = 10);

    /**
     * @brief Follow the path interpolated by the given coordinates
     * @param x The x-coordinates
     * @param y The y-coordinates
     * @param tolerance The distance tolerance for the path (ending condition)
     * @param num_points The number of points to interpolate
    */
    void follow_path(std::vector<double> x, std::vector<double> y, double tolerance, int num_points = 50);

    /**
     * @brief Follow the given path
     * @param path The path object to follow
    */
    void follow_path(Path path, double tolerance = 5.0);

    /**
     * @brief Turn to the given angle
     * @param angle The angle to turn to, in radians
    */
    void turn_to(double angle);

    /**
     * @brief Turn by the given angle
     * @param angle The angle to turn by, in radians
    */
    void turn(double angle);
};

#endif



/*
- BotBase();
- BotBase(AbstractMotorGroup* left, AbstractMotorGroup* right, double base_width, double wheel_radius, double pursuit_distance, double gear_multiplier, int thread_sleep);

- BotBase& set_left(AbstractMotorGroup* left);
- BotBase& set_right(AbstractMotorGroup* right);
- template<typename... Args> 
    BotBase& set_left(vex::motor* m1, Args ... m);
- BotBase& set_left(vex::motor* m1);
- template<typename... Args>
    BotBase& set_right(vex::motor* m1, Args ... m);
- BotBase& set_right(vex::motor* m1);

- BotBase& set_base_width(double base_width);
- BotBase& set_wheel_radius(double wheel_radius);
- BotBase& set_pursuit_distance(double pursuit_distance);
- BotBase& set_gear_multiplier(double gear_multiplier);
- BotBase& set_thread_sleep(int thread_sleep);

- void follow_path(std::vector<double> x, std::vector<double> y, double tolerance, int num_points);
- void follow_path(Path path, double tolerance);

- void turn_to(double angle);
- void turn(double angle);

- void move(double x, double y, double tolerance);
- void fwd(double distance, double tolerance);
- void bwd(double distance, double tolerance);
*/