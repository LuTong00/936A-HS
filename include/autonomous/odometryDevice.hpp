#ifndef ODOMETRY_HPP
#define ODOMETRY_HPP

#include <vex.h>
#include <autonomous/abstractMotorGroup.hpp>
#include <vector>
#include <cmath>

/**
 * @brief The odometry class to track the position and rotation of the robot.
 * @attention The odometry class will only function within scope, so make sure it is managed by another object.
*/
class Odometry {
    /**
     * @brief Tracking function for odometry. Updates the position and rotation of the robot. 
     * @attention This function is NOT meant to be called directly.
     * @param o The odometry object as a void*. Immediately cast back to an Odometry*.
    */
    friend int track(void* o);

    /**
     * @brief Thread to update the odometry object's position and rotation.
     * @attention This thread is managed by the Odometry object. It does NOT detach; therefore, the Odometry
       object must remain in scope throughout the desired period of coordinate tracking, either through
       management by another object or through the use of a blocking function.
    */
    vex::thread tracking;

    /**
     * @brief The left motor group.
    */
    AbstractMotorGroup* left;

    /**
     * @brief The right motor group.
    */
    AbstractMotorGroup* right;

    /**
     * @brief The width of the base.
     * @attention Units must be consistent with wheel_radius.
    */
    double base_width;

    /**
     * @brief The radius of the wheel.
     * @attention Units must be consistent with base_width.
    */
    double wheel_radius;

    /**
     * @brief The gear ratio between the motor and the wheel.
    */
    double gear_multiplier;

    /**
     * @brief The x position of the robot.
    */
    double x_position;

    /**
     * @brief The y position of the robot.
    */
    double y_position;

    /**
     * @brief The rotation of the robot.
     * @attention Units are in radians.
    */
    double rotation_value;

    /**
     * @brief The measure of the left encoders.
    */
    double left_position;

    /**
     * @brief The measure of the right encoders.
    */
    double right_position;

    /**
     * @brief The last measure of the left encoders.
    */
    double last_left_position;

    /**
     * @brief The last measure of the right encoders.
    */
    double last_right_position;

    /**
     * @brief The change in measure of the left encoders.
    */
    double delta_left;

    /**
     * @brief The change in measure of the right encoders.
    */
    double delta_right;

    /**
     * @brief The change in x position.
    */
    double delta_x;

    /**
     * @brief The change in y position.
    */
    double delta_y;

    /**
     * @brief The change in rotation.
     * @attention Units are in radians.
    */
    double delta_rotation;

    /**
     * @brief The x coordinate of the center of rotation.
    */
    double center_x;

    /**
     * @brief The y coordinate of the center of rotation.
    */
    double center_y;

    /**
     * @brief The radius of the rotation.
    */
    double center_radius;

    /**
     * @brief The local translation in the transformed basis.
    */
    double local_x_translation;

    /**
     * @brief The local rotation in the transformed basis.
     */
    double local_offset;

    /**
     * @brief Get the average value of the left encoders.
     * @return The average value as a double.
    */
    double get_left();

    /**
     * @brief Get the average value of the right encoders.
     * @return The average value as a double.
    */
    double get_right();

    /**
     * @brief The sleep time for the tracking thread, in microseconds.
    */
    int thread_sleep;
public:
    /**
     * @brief The constructor for the Odometry class. Automatically construct tracking thread.
     * @param left The left motor group.
     * @param right The right motor group.
     * @param base_width The width of the base.
     * @param wheel_radius The radius of the wheel.
     * @param gear_multiplier The multiplier associated with the gear ratio and motor cartridges.
     * @param thread_sleep The sleep time for the tracking thread, in microseconds.
     * @attention All units must be consistent with odometry.
    */
    Odometry(AbstractMotorGroup* left, AbstractMotorGroup* right, double base_width, double wheel_radius, double gear_multiplier, int thread_sleep = 10);

    /**
     * @brief Retrieve the x coordinate.
     * @return The x coordinate as a double.
    */
    double x();

    /**
     * @brief Retrieve the y coordinate.
     * @return The y coordinate as a double.
    */
    double y();

    /**
     * @brief Retrieve the rotation.
     * @return The rotation as a double, in radians.
    */
    double rotation();

    /**
     * @brief Set the position and rotation of the robot.
     * @param x The x coordinate.
     * @param y The y coordinate.
     * @param rotation The rotation, in radians.
     */
    void set_pose(double x, double y, double rotation);
};

#endif