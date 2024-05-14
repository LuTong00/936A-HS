#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <utility>
#include <stdexcept>
#include <iostream>
#include <ostream>
#include <vector>
#include <map>
#include <cmath>

/**
 * @brief The Matrix class implements the mathematical matrix. It supports 
   fundamental matrix operations, reduced row echelon form, determinant,
   and inversion.
*/
class Matrix {
    /**
     * @brief The shape of the matrix as a pair {m, n}, where the matrix has m rows and n columns.
    */
    std::pair<int, int> shape;

    /**
     * @brief The underlying memory of the matrix as a 2D std::vector.
    */
    std::vector<std::vector<double>> memory;
    
    /**
     * @brief Swap two rows of the matrix in-place.
     * @param r1 The first row.
     * @param r2 The second row.
    */
    void swap_row(int r1, int r2);

    /**
     * @brief Perform row operations on a matrix in-place.
     * @param row The row to which results should be assigned.
     * @param operations A map of {int, double} pairs giving the row and the scale factor; 
       {r_k, l} adds l*r_k to the result.
    */
    void row_operation(int row, std::map<int, double> operations);

public:

    /**
     * @brief Access underlying memory with matrix values. M[i][j] behaves like M.memory[i][j].
     * @param index The index of the row to be accessed. Elements can be accessed from this row 
       using another operator[].
     * @return A vector representing row "index".
    */
    std::vector<double>& operator[] (int index);

    /**
     * @brief Default constructor; leaves the matrix with a shape of {0, 0} and default-constructed 
       vector as memory.
    */
    Matrix();

    /**
     * @brief Copy constructor.
     * @param other The matrix to be deep-copied.
    */
    Matrix(Matrix& other);

    /**
     * @brief Move constructor.
     * @param other The matrix whose resources are to be transferred.
    */
    Matrix(Matrix&& other);

    /**
     * @brief Fill-value constructor/
     * @param m_shape The shape of the matrix as a pair {m, n}, where the matrix has m rows and n columns.
     * @param value The value which will fill the matrix.
    */
    Matrix(std::pair<int, int> m_shape, double value);

    /**
     * @brief Array-fill constructor/
     * @param m_shape The shape of the matrix as a pair {m, n}, where the matrix has m rows and n columns.
     * @param values An array of doubles which will fill the matrix.
    */
    Matrix(std::pair<int, int> m_shape, double * values);

    /**
     * @brief Vector constructor.
     * @param values A 2D std::vector of values, which will fill the matrix's values.
     * @warning Each of the std::vector<double>'s in values must have the same length. 
       Shape will be inferred.
    */
    Matrix(std::vector<std::vector<double>> values);

    /**
     * @brief Copy assignment.
     * @param other The matrix to be copied.
     * @return A reference to *this to allow operator chaining.
    */
    Matrix& operator= (Matrix& other);

    /**
     * @brief Move assignment.
     * @param other The matrix whose resources are to be transferred.
     * @return A reference to *this.
    */
    Matrix& operator= (Matrix&& other);

    /**
     * @brief Negates all values in the matrix.
     * @return The additive inverse of the matrix, returned by value.
    */
    Matrix operator- ();

    /**
     * @brief Adds a matrix.
     * @param other The matrix to be added.
     * @warning The matrices must have the same shape.
     * @return The result of the addition, returned by value.
    */
    Matrix operator+ (Matrix& other);

    /**
     * @brief Subtracts a matrix.
     * @param other The matrix to be subtracted.
     * @warning The matrices must have the same shape.
     * @return The result of the subtraction, returned by value.
    */
    Matrix operator- (Matrix& other);

    /**
     * @brief Multiplies a matrix.
     * @param other The matrix to be multiplied.
     * @warning The matrix "other" must have the same number of columns as the matrix "*this" has rows.
     * @return The result of the multiplication, returned by value.
    */
    Matrix operator* (Matrix& other);

    /**
     * @brief Augments a matrix by extending another matrix to the current one on axis 0.
     * @param other The matrix which will be attached.
     * @warning The matrices must have the same number of rows.
     * @return The augmented matrix given by [*this | other], returned by value.
    */
    Matrix augment(Matrix& other);
    
    /**
     * @brief Inverts the rows and columns of the matrix.
     * @return The transpose matrix M with M_i,j = (*this)_j,i; returned by value.
    */
    Matrix transpose();

    /**
     * @brief Get the Reduced Row-Echelon Form of the matrix.
     * @return The unique RREF of the matrix, returned by value.
    */
    Matrix rref();

    /**
     * @brief Get the inverse of the matrix.
     * @param check_det Whether or not to check for 0 determinant; if the
       inverse is guaranteed to exist, this may be set to false for decreased computation.
       Default: true.
     * @return The inverse of the matrix if it exists, returned by value.
    */
    Matrix inverse(bool check_det = true);

    /**
     * @brief Scalar operation of the matrix.
     * @param scalar The scalar by which to multiply the matrix.
     * @return The result of the scalar operation, returned by value.
    */
    Matrix operator* (double scalar);

    /**
     * @brief Scalar operation of the matrix.
     * @param scalar The scalar by which to divide the matrix.
     * @return The result of the scalar operation, returned by value.
    */
    Matrix operator/ (double scalar);

    /**
     * @brief Get the determinant of the matrix.
     * @return The determinant of the matrix as a double.
     * @details Implemented by performing row operations to reduce the matrix into a 
      row-equivalent upper triangular matrix, then taking the product of the main diagonal.
    */
    double determinant();

    /**
     * @brief Output utilities
     * @return The stream, allowing operator chaining.
    */
    friend std::ostream& operator << (std::ostream& os, Matrix& M);

    /**
     * @brief Output utilities
     * @return The stream, allowing operator chaining.
    */
    friend std::ostream& operator << (std::ostream& os, Matrix&& M);
};

/**
 * @brief Get the identity matrix
 * @param n The number of dimensions
 * @return The nxn identity matrix I_n
*/
Matrix identity(int n);

#endif