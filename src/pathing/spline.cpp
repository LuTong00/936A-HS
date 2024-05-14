#include <pathing/spline.hpp>

Cubic::Cubic(double a, double b, double c, double d): a(a), b(b), c(c), d(d) {}

int CubicSpline::get_segment(double x) {
    int i = coefs.size() - 1;
    while (boundaries[i] > x) {
        --i;
        if (i == 0) {
            return 0;
        }
    }
    return i;
}

CubicSpline::CubicSpline(std::vector<double> x, std::vector<double> y): boundaries(x) {
    if (x.size() != y.size()) {
        std::cerr << "Inhomogenous vector shapes\n";
        return;
        // throw std::logic_error("Inhomogenous vector shapes");
    }
    boundaries = x;
    int n = x.size() - 1;
    coefs = std::vector<Cubic>(n, Cubic(0, 0, 0, 0));
    M = Matrix(std::make_pair(n * 4, n * 4 + 1), 0.0);
    // initial conditions
    // f''1(x0) = 0
    M[0][0] = x[0] * 6.0;
    M[0][1] = 2.0;
    // fn(xn-1) = yn-1
    M[n * 4 - 3][n * 4 - 4] = pow(x[n - 1], 3.0);
    M[n * 4 - 3][n * 4 - 3] = pow(x[n - 1], 2.0);
    M[n * 4 - 3][n * 4 - 2] = x[n - 1];
    M[n * 4 - 3][n * 4 - 1] = 1.0;
    // fn(xn) = yn
    M[n * 4 - 2][n * 4 - 4] = pow(x[n], 3.0);
    M[n * 4 - 2][n * 4 - 3] = pow(x[n], 2.0);
    M[n * 4 - 2][n * 4 - 2] = x[n];
    M[n * 4 - 2][n * 4 - 1] = 1.0;
    // f''n(xn) = 0
    M[n * 4 - 1][n * 4 - 4] = x[n] * 6.0;
    M[n * 4 - 1][n * 4 - 3] = 2.0;
    // n - 1 quadruples of conditions
    for (int i = 0; i < n - 1; ++i) {
        int bi = i * 4 + 1, bj = i * 4;
        // fk(xk-1) = yk-1
        M[bi][bj] = pow(x[i], 3.0);
        M[bi][bj + 1] = pow(x[i], 2.0);
        M[bi][bj + 2] = x[i];
        M[bi][bj + 3] = 1.0;
        // fk(xk) = yk
        M[bi + 1][bj] = pow(x[i + 1], 3.0);
        M[bi + 1][bj + 1] = pow(x[i + 1], 2.0);
        M[bi + 1][bj + 2] = x[i + 1];
        M[bi + 1][bj + 3] = 1.0;
        // f'k(xk) - f'k+1(xk) = 0
        M[bi + 2][bj] = pow(x[i + 1], 2.0) * 3.0;
        M[bi + 2][bj + 1] = x[i + 1] * 2.0;
        M[bi + 2][bj + 2] = 1.0;
        M[bi + 2][bj + 4] = -pow(x[i + 1], 2.0) * 3.0;
        M[bi + 2][bj + 5] = -x[i + 1] * 2.0;
        M[bi + 2][bj + 6] = -1.0;
        // f''k(xk) - f''k+1)(xk) = 0
        M[bi + 3][bj] = x[i + 1] * 6.0;
        M[bi + 3][bj + 1] = 2.0;
        M[bi + 3][bj + 4] = -x[i + 1] * 6.0;
        M[bi + 3][bj + 5] = -2.0;
    }
    // augmented column (values)
    for (int i = 0; i < n; ++i) {
        int bi = i * 4 + 1, bj = n * 4;
        M[bi][bj] = y[i];
        M[bi + 1][bj] = y[i + 1];
    }
    Matrix R = M.rref();
    // extract values
    std::vector<double> values(n * 4, 0.0);
    for (int i = 0; i < n * 4; ++i) {
        values[i] = R[i][n * 4];
    }
    // store as params
    for (int i = 0; i < n; ++i) {
        coefs[i] = Cubic(values[i * 4], values[i * 4 + 1], values[i * 4 + 2], values[i * 4 + 3]);
    }
}

std::vector<double> CubicSpline::operator() (std::vector<double> x) {
    std::vector<double> y;
    for (auto i : x) {
        Cubic coef = coefs[get_segment(i)];
        double a = coef.a, b = coef.b, c = coef.c, d = coef.d;
        double value = a * i * i * i + b * i * i + c * i + d;
        y.push_back(value);
    }
    return y;
}

std::vector<double> linspace(double start, double end, int num_points) {
    std::vector<double> result;
    if (num_points <= 0) {
        return result;
    }
    double step = (end - start) / (num_points - 1);
    for (int i = 0; i < num_points; ++i) {
        double value = start + i * step;
        result.push_back(value);
    }
    return result;
}