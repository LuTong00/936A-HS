#include <bot.hpp>

// AbstractMotorGroup left;
// AbstractMotorGroup right;
// Odometry odom;
// vex::controller controller;
// vex::brain brain;
// double base_width;
// double wheel_radius;
// double pursuit_distance;
// double gear_multiplier;
// int thread_sleep;

BotBase::BotBase(AbstractMotorGroup* left, AbstractMotorGroup* right, 
                 double base_width, double wheel_radius, double pursuit_distance, double gear_multiplier, int thread_sleep): 
                    left(left), right(right),
                    odom(left, right, base_width, wheel_radius, gear_multiplier, thread_sleep),
                    base_width(base_width), wheel_radius(wheel_radius), pursuit_distance(pursuit_distance), gear_multiplier(gear_multiplier), 
                    thread_sleep(thread_sleep) {std::cout << "Construction done\n";}

void BotBase::follow_path(std::vector<double> x, std::vector<double> y, double tolerance, int num_points) {
    Path path(x, y, num_points);
    follow_path(path, tolerance);
}

void BotBase::follow_path(Path path, double tolerance) {
    PurePursuit pursuit(path, pursuit_distance);
    auto distance = [] (double x1, double y1, double x2, double y2) -> double {return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));};
    Point end = path.points[path.points.size() - 1];
    while (distance(odom.x(), odom.y(), end.x, end.y) > tolerance) {
        auto steering = pursuit.get_relative_steering(odom.x(), odom.y(), odom.rotation(), base_width);
        left -> spin(vex::fwd, steering.first, vex::pct);
        right -> spin(vex::fwd, steering.second, vex::pct);
        vex::this_thread::sleep_for(1);
    }
}

void BotBase::turn_to(double angle) {

}

void BotBase::turn(double angle) {

}