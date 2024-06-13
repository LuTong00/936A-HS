#include <pathing/path.hpp>

Path::Path(std::vector<double> x, std::vector<double> y, int num_points) {
    if (x.size() != y.size()) {
        std::cerr << "Inhomogenous vector lengths\n";
        return;
    }
    std::vector<double> p(x.size(), 0.0);
    for (int i = 1; i < p.size(); ++i) {
        p[i] = p[i - 1] + 1.0;
    }
    CubicSpline x_spline(p, x);
    CubicSpline y_spline(p, y);

    std::vector<double> p_interp = linspace(p[0], p[p.size() - 1], num_points);
    
    std::vector<double> x_interp = x_spline(p_interp);
    std::vector<double> y_interp = y_spline(p_interp);

    for (int i = 0; i < num_points; ++i) {
        points.push_back(Point(x_interp[i], y_interp[i]));
    }
}

int Path::get_segment(Point point) {
    return get_segment(point.x, point.y);
}

int Path::get_segment(double x, double y) {
    int i = points.size() - 1;
    while (
        (
            (
                !(
                    (points[i - 1].x <= x && x <= points[i].x) || 
                    (points[i - 1].x >= x && x >= points[i].x)
                )
                // either x is not in the range
            ) || (
                !(
                    (points[i - 1].y <= y && y <= points[i].y) || 
                    (points[i - 1].y >= y && y >= points[i].y)
                )
                // or y is not in the range
            )
        )
    ) {
        --i;
        if (i == 0) {
            return 0;
        }
    }
    return i - 1;
}

double Path::distance_to_end(Point point) {
    return distance_to_end(point.x, point.y);
}

double Path::distance_to_end(double x, double y) {
    int segment = get_segment(x, y);
    Point next = points[segment + 1];
    double distance = sqrt((x - next.x) * (x - next.x) + (y - next.y) * (y - next.y));
    for (int i = segment + 2; i < points.size(); ++i) {
        Point p1 = points[i];
        Point p2 = points[i - 1];
        distance += sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
    }
    return distance;
}

Point Path::closest_point(double x, double y) {
    int min_distance = 1e9;
    Point closest;
    for (int i = 0; i < points.size(); ++i) {
        double distance = sqrt((x - points[i].x) * (x - points[i].x) + (y - points[i].y) * (y - points[i].y));
        if (distance < min_distance) {
            min_distance = distance;
            closest = points[i];
        }
    }
    return closest;
}