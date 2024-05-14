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