#ifndef PURE_PURSUIT_HPP
#define PURE_PURSUIT_HPP

#include <vector>
#include <pathing/path.hpp>

/**
 * @brief The PurePursuit class to follow a path.
*/
class PurePursuit {
    /**
     * @brief The path to follow, interpolated from waypoints.
    */
    Path path;

    /**
     * @brief The lookahead distance.
     * @attention The units must be consistent with the units for odometry.
    */
    double lookahead;

public:
    /**
     * @brief The constructor for the PurePursuit class.
     * @param path The path to follow, as a Path object.
     * @param lookahead The lookahead distance.
     * @attention The units for the lookahead distance must be consistent with the units for odometry.
    */
    PurePursuit(Path path, double lookahead);

    /**
     * @brief The constructor for the PurePursuit class.
     * @param x The x coordinates of the waypoints.
     * @param y The y coordinates of the waypoints.
     * @param num_points The number of points to interpolate in total.
     * @param lookahead The lookahead distance.
     * @attention x and y are the ACTUAL waypoint coordinates; do NOT parametrize as this is done automatically
       within the constructor. Units for x, y, and lookahead must be identical to odometry units.
    */
    PurePursuit(std::vector<double> x, std::vector<double> y, int num_points, double lookahead);

    /**
     * @brief The accessor for the lookahead distance.
     * @return A reference to the lookahead distance.
    */
    double& lookahead_distance();

    /**
     * @brief Get the target point for the robot to follow.
     * @param x_bot The x position of the robot.
     * @param y_bot The y position of the robot.
     * @attention Units must be consistent with odometry.
     * @return The target point for the robot to follow. The point returned satisfies the conditions:
         The point is on the path; the point is exactly lookahead distance away from the robot;
         the point is the closest to the end of the path. If no such point is found, then the
         point is the closest waypoint to the robot.
    */
    Point get_target(double x_bot, double y_bot);

    /**
     * @brief Get the relative steering power for the robot to follow.
     * @param x_bot The x position of the robot.
     * @param y_bot The y position of the robot.
     * @param theta_bot The rotation of the robot, in radians.
     * @param width_bot The width of the robot.
     * @attention Units must be consistent with odometry.
     * @attention The steering power will be negative when the robot is more than half a revolution away
       from the target point.
     * @attention The steering power is normalized so that the entries sum to 100.
     * @return A pair of doubles representing the relative left and right steering power.
    */
    std::pair<double, double> get_relative_steering(double x_bot, double y_bot, double theta_bot, double width_bot);
};

#endif