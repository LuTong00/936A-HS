#ifndef VIRTUAL_ODOMETRY_HPP
#define VIRTUAL_ODOMETRY_HPP

#include <vex.h>
#include <vector>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <thread>

int virtual_track(void* o);

class VirtualOdometry {
    friend int virtual_track(void* o);
    vex::thread tracking;
    double base_width, wheel_radius, gear_multiplier;
    double x_position, y_position, rotation_value;
    double left_position, right_position;
    double last_left_position, last_right_position;
    double delta_left, delta_right;
    double delta_x, delta_y, delta_rotation;
    double center_x, center_y, center_radius;
    double local_x_translation, local_offset;
    double get_left() {
        double k;
        std::cout << "Input left: ";
        std::cin >> k;
        return k;
    }
    double get_right() {
        double k;
        std::cout << "Input right: ";
        std::cin >> k;
        return k;
    }
public:
    VirtualOdometry(double base_width, double wheel_radius, double gear_multiplier) {
        VirtualOdometry::base_width = base_width;
        VirtualOdometry::wheel_radius = wheel_radius;
        VirtualOdometry::gear_multiplier = gear_multiplier;
        VirtualOdometry::tracking = vex::thread(virtual_track, (void*) this);
    }
    double x() {
        return VirtualOdometry::x_position;
    }
    double y() {
        return VirtualOdometry::y_position;
    }
    double rotation() {
        return VirtualOdometry::rotation_value;
    }
};

int virtual_track(void* o) {
    VirtualOdometry* odometry = (VirtualOdometry*) o;
    // reset all positions and variables to zero
    odometry -> last_left_position = 0.0;
    odometry -> last_right_position = 0.0;
    odometry -> x_position = 0.0;
    odometry -> y_position = 0.0;
    odometry -> rotation_value = 0.0;

    while (true) {
        // calculate the change in positions
        odometry -> delta_left = odometry -> get_left();
        odometry -> delta_right = odometry -> get_right();

        // update the last positions
        odometry -> last_left_position = odometry -> left_position;
        odometry -> last_right_position = odometry -> right_position;

        // calculate the change in rotation
        odometry -> delta_rotation = (odometry -> delta_right - odometry -> delta_left) / odometry -> base_width;
        // calculate the local rotation offset
        odometry -> local_offset = odometry -> rotation_value + odometry -> delta_rotation * 0.5;

        // casework on the change in rotation
        if (odometry -> delta_rotation != 0.0) {
            // nonzero angle: calculate the center of rotation and the local translation
            odometry -> center_radius = odometry -> delta_left / odometry -> delta_rotation + odometry -> base_width * 0.5;
            odometry -> local_x_translation = sin(odometry -> delta_rotation * 0.5) * odometry -> center_radius * 2.0;
        } else {
            // zero angle: translation equals the left/right change in positions
            odometry -> local_x_translation = odometry -> delta_left;
        }

        // Update positions based on the changes in positions
        odometry -> x_position += odometry -> local_x_translation * cos(odometry -> local_offset);
        odometry -> y_position += odometry -> local_x_translation * sin(odometry -> local_offset);
        odometry -> rotation_value += odometry -> delta_rotation;

        printf("(%.5f, %.5f) heading %.5f\n", odometry -> x_position, odometry -> y_position, odometry -> rotation_value);
    }
}

class Manager {
public:
    VirtualOdometry v;
    Manager(): v(VirtualOdometry(30, 10, 1)) {
        std::cout << "Manager of odometry is constructed\n";
    }
};

void test_virtualOdometryDevice() {
    Manager bot;
    std::cout << "Executing in calling thread\n";
    while (1);
}

#endif