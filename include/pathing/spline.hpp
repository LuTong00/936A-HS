#ifndef SPLINE_HPP
#define SPLINE_HPP

#include <pathing/matrix.hpp>
#include <vector>
#include <cmath>

/**
 * @brief The Cubic structure represents a cubic polynomial with its coefficients.
*/
struct Cubic {
    double a, b, c, d;
    Cubic(double a, double b, double c, double d);
};

/**
 * @brief The CubicSpline class implements cubic spline interpolation.
*/
class CubicSpline {
    /**
     * @brief The augmented matrix of operations
    */
    Matrix M;

    /**
     * @brief A container storing each Cubic object, encoding the piecewise parameters.
    */
    std::vector<Cubic> coefs;

    /**
     * @brief A container storing the spline point x-coordinates, used to determine 
       which piece's parameters to use.
    */
    std::vector<double> boundaries;

public:
    /**
     * @brief Get the index of the piece associated with a value.
     * @param x The value of the point to be interpolated.
     * @return An integer (0-based) representing the index of the piece.
    */
    int get_segment(double x);

    /**
     * @brief Constructor for the CubicSpline. 
     * @param x The x values of the points.
     * @param y The y values of the points.
    */
    CubicSpline(std::vector<double> x, std::vector<double> y);

    /**
     * @brief Overloaded call operator for the CubicSpline.
     * @param x The x values of points to be interpolated.
     * @return A std::vector<double> of points, representing the result of the interpolation.
    */
    std::vector<double> operator() (std::vector<double> x);
};


/**
 * @brief Generate equally-spaced numbers given endpoints. Identical to np.linspace in Python.
 * @param start The minimum value.
 * @param end The maximum value.
 * @param num_points The number of equidistant points to be generated.
 * @return A std::vector<double> of length num_points, whose endpoints are given by start and end 
   and whose elements form an arithmetic sequence.
*/
std::vector<double> linspace(double start, double end, int num_points);

#endif