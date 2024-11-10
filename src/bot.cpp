#include <bot.hpp>

BotBase::BotBase(AbstractMotorGroup* left, AbstractMotorGroup* right, 
                 double base_width, double wheel_radius, double pursuit_distance, double gear_multiplier, 
                 double initial_x, double initial_y, double initial_rotation, int thread_sleep): 
                    left(left), right(right),
                    odom(left, right, base_width, wheel_radius, gear_multiplier, thread_sleep),
                    base_width(base_width), wheel_radius(wheel_radius), pursuit_distance(pursuit_distance), gear_multiplier(gear_multiplier), 
                    thread_sleep(thread_sleep) {
    odom.set_pose(initial_x, initial_y, initial_rotation);
}

void BotBase::follow_path(std::vector<double> x, std::vector<double> y, double tolerance, double speed_factor, int num_points) {
    Path path(x, y, num_points);
    follow_path(path, tolerance, speed_factor);
}

void BotBase::follow_path(Path path, double tolerance, double speed_factor) {
    PurePursuit pursuit(path, pursuit_distance);
    auto distance = [] (double x1, double y1, double x2, double y2) -> double {return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));};
    Point end = path.points[path.points.size() - 1];
    while (distance(odom.x(), odom.y(), end.x, end.y) > tolerance) {
        auto steering = pursuit.get_relative_steering(odom.x(), odom.y(), odom.rotation(), base_width);
        left -> spin(vex::fwd, steering.first * speed_factor, vex::pct);
        right -> spin(vex::fwd, steering.second * speed_factor, vex::pct);
        vex::this_thread::sleep_for(thread_sleep);
    }
    left -> stop();
    right -> stop();
}

void BotBase::turn_to(double angle, double tolerance, double speed_factor) {
    static auto nearest_coterminal = [] (double rotation, double target) -> double {
        static double pi2 = M_PI * 2, divpi2 = 1 / pi2;
        return floor((rotation - target + M_PI) * divpi2) * pi2 + target;
    };
    double target_rotation = nearest_coterminal(odom.rotation(), angle);
    double change = target_rotation - odom.rotation();
    turn(change, tolerance, speed_factor);
}

void BotBase::turn(double angle, double tolerance, double speed_factor) {
    double target = odom.rotation() + angle;
    //PID pid(15.0, 0.001, 25.0, 1.0, 100.0, 0.9999); // kp, ki, kd, min, max, gamma
    PID pid(45.0, 0.0025, 10.0, 0, 100, 0.9999); // kp, ki, kd, min, max, gamma
    pid.set_target(target);
    while (fabs(odom.rotation() - target) > tolerance) {
        double output = pid.calculate(odom.rotation()) * speed_factor;
        left -> spin(vex::fwd, -output, vex::pct);
        right -> spin(vex::fwd, output, vex::pct);
        vex::this_thread::sleep_for(thread_sleep);
    }
    left -> stop();
    right -> stop();
}

void BotBase::forward(double distance, double tolerance, double speed_factor) {
    double x1 = odom.x(), y1 = odom.y();
    double rotation = odom.rotation();
    double x2 = x1 + distance * cos(rotation), y2 = y1 + distance * sin(rotation);
    follow_path({x1, x2}, {y1, y2}, tolerance, speed_factor, 50);
}

void coordinate_display(void* b) {
    BotBase * base = (BotBase *) b;
    //printf("[");
    while (true) {
        printf("(%.5f, %.5f, %.5f),\n", base -> odom.x(), base -> odom.y(), base -> odom.rotation());
        //printf("(%.5f, %.5f)\n", base -> odom.x(), base -> odom.y());
        vex::this_thread::sleep_for(50);
    }
    return;
}