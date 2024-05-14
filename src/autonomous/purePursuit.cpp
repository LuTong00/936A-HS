#include <autonomous/purePursuit.hpp>

PurePursuit::PurePursuit(Path path, double lookahead): path(path), lookahead(lookahead) {}

PurePursuit::PurePursuit(std::vector<double> x, std::vector<double> y, int num_points, double lookahead) {
    path = Path(x, y, num_points);
    this -> lookahead = lookahead;
}

double& PurePursuit::lookahead_distance() {
    return lookahead;
}

Point PurePursuit::get_target(double x_bot, double y_bot) {
    // Solve for the intersection between a circle and a line segment; iterate in reverse
    for (int i = path.points.size() - 1; i > 0; --i) {
        double x1, y1, x2, y2;
        // Retrieve the line in slope-intercept form y=mx+b
        if (path.points[i].x == path.points[i - 1].x) {
            // Deal with the case where the line is vertical
            double determinant = lookahead * lookahead - (path.points[i].x - x_bot) * (path.points[i].x - x_bot);
            if (determinant < 0) {
                // No solution
                continue;
            }
            x1 = x2 = path.points[i].x;
            y1 = y_bot + sqrt(determinant);
            y2 = y_bot - sqrt(determinant);
        } else {
            // Deal with the case where the line is not vertical
            double m = (path.points[i].y - path.points[i - 1].y) / (path.points[i].x - path.points[i - 1].x);
            double b = path.points[i].y - m * path.points[i].x;
            // Retrieve the intersection between circle (x-x_bot)^2+(y-y_bot)^2=lookahead^2 and line y=mx+b
            // Quadratic coefficients
            double A = m * m + 1.0;
            double B = (m * b - m * y_bot - x_bot) * 2.0;
            double C = x_bot * x_bot + y_bot * y_bot + b * b - lookahead * lookahead - b * y_bot * 2.0;
            double determinant = B * B - A * C * 4.0;
            if (determinant < 0) {
                // No solution
                continue;
            }
            x1 = (-B + sqrt(determinant)) / (A * 2.0);
            y1 = m * x1 + b;
            x2 = (-B - sqrt(determinant)) / (A * 2.0);
            y2 = m * x2 + b;
        }
        // Determine whether the found intersection points are valid (fall between the bounding points)
        bool p1_valid = false, p2_valid = false;
        if (path.points[i - 1].x <= x1 and x1 <= path.points[i].x) {
            p1_valid = true;
        }
        if (path.points[i - 1].x <= x2 and x2 <= path.points[i].x) {
            p2_valid = true;
        }
        if (p1_valid and p2_valid) {
            // Both points are valid; return the point closer to path.points[i]
            if (sqrt((x1 - path.points[i].x) * (x1 - path.points[i].x) + (y1 - path.points[i].y) * (y1 - path.points[i].y)) < 
                sqrt((x2 - path.points[i].x) * (x2 - path.points[i].x) + (y2 - path.points[i].y) * (y2 - path.points[i].y))) {
                return Point(x1, y1);
            } else {
                return Point(x2, y2);
            }
        } else if (p1_valid) {
            // Only the first point is valid
            return Point(x1, y1);
        } else if (p2_valid) {
            // Only the second point is valid
            return Point(x2, y2);
        }
    }
    // If no points are found, look for the nearest Point
    double min_distance = 1e9;
    int min_index = 0;
    for (int i = 0; i < path.points.size(); ++i) {
        double distance = sqrt((path.points[i].x - x_bot) * (path.points[i].x - x_bot) + (path.points[i].y - y_bot) * (path.points[i].y - y_bot));
        if (distance < min_distance) {
            min_distance = distance;
            min_index = i;
        }
    }
    return path.points[min_index];
}

std::pair<double, double> PurePursuit::get_relative_steering(double x_bot, double y_bot, double theta_bot, double width_bot) {
    Point target = get_target(x_bot, y_bot); // Retrieve the target point
    double dx = target.x - x_bot; // Calculate the relative x
    double dy = target.y - y_bot; // Calculate the relative y
    double angle = atan2(dy, dx); // Calculate the argument of the relative vector
    double alpha = angle - theta_bot; // Calculate the relative angle
    double sine = sin(alpha); // Calculate the sine of the relative angle
    double central_radius = lookahead / sine * 0.5; // Calculate the central radius
    
    // Calculate steering values
    double left_steering = central_radius - width_bot * 0.5; 
    double right_steering = central_radius + width_bot * 0.5;
    double scale = 100.0 / (left_steering + right_steering);
    if (sine < 0) {
        scale = -scale;
    }
    return std::make_pair(left_steering * scale, right_steering * scale);
}