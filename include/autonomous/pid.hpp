#ifndef PID_HPP
#define PID_HPP

#include <iostream>

/**
 * @brief The PID controller class.
*/
class PID {
private:
    /**
     * @brief The gain constant of the PID controller. Fine tune.
    */
    double kp, ki, kd;

    /**
     * @brief The target value of the PID controller.
    */
    double target;

    /**
     * @brief The integral value of the PID controller.
    */
    double integral;

    /**
     * @brief The last error of the PID controller.
    */
    double last_error; 

    /**
     * @brief The absolute value of the minimum output of the PID controller.
    */
    double minimum_output;

    /**
     * @brief The absolute value of the maximum output of the PID controller.
    */
    double maximum_output;

    /**
     * @brief The integral discount value of the PID controller (earlier values get "forgotten").
    */
    double gamma;

public:
    /**
     * @brief The constructor for the PID class.
     * @param kp The proportional gain constant.
     * @param ki The integral gain constant.
     * @param kd The derivative gain constant.
     * @param minimum_output The absolute value of the minimum output of the PID controller.
     * @param maximum_output The absolute value of the maximum output of the PID controller.
     * @param gamma The integral discount value of the PID controller (earlier values get "forgotten").
    */
    PID(double kp, double ki, double kd, double minimum_output = 0.5, double maximum_output = 1.0, double gamma = 0.9999);

    /**
     * @brief Sets the target value of the PID controller.
     * @param target The target value of the PID controller.
    */
    void set_target(double target);

    /**
     * @brief Calculates the output of the PID controller.
     * @param value The current value of the PID controller.
     * @return The output value of the PID controller.
    */
    double calculate(double value);

    /**
     * @brief Resets the integral and last error of the PID controller.
    */
    void reset();
};

#endif