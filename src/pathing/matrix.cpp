#include <pathing/matrix.hpp>

void Matrix::swap_row(int r1, int r2) {
    if (r1 == r2) {
        return;
    }
    std::swap(memory[r1], memory[r2]);
}

void Matrix::row_operation(int row, std::map<int, double> operations) {
    std::vector<double> result(shape.second, 0);
    for (auto kv_pair : operations) {
        int row = kv_pair.first;
        double scalar = kv_pair.second;
        for (int i = 0; i < shape.second; ++i) {
            result[i] += memory[row][i] * scalar;
        }
    }
    memory[row] = result;
}

std::vector<double>& Matrix::operator[] (int index) {
    return memory[index];
}

Matrix::Matrix() {
    shape = std::make_pair(0, 0);
    memory = std::vector<std::vector<double>>();
}

Matrix::Matrix(Matrix& other) {
    shape = other.shape;
    memory = other.memory;
}

Matrix::Matrix(Matrix&& other) {
    shape = std::move(other.shape);
    memory = std::move(other.memory);
    other.shape = std::make_pair(0, 0);
    other.memory = std::vector<std::vector<double>>();
}

Matrix::Matrix(std::pair<int, int> m_shape, double value) {
    shape = m_shape;
    memory.assign(shape.first, std::vector<double>(shape.second, value));
}

Matrix::Matrix(std::pair<int, int> m_shape, double * values) {
    shape = m_shape;
    memory.assign(shape.first, std::vector<double>(shape.second, 0.0));
    for (int i = 0; i < shape.first; ++i) {
        for (int j = 0; j < shape.second; ++j) {
            int index = i * shape.second + j;
            memory[i][j] = values[index];
        }
    }
}

Matrix::Matrix(std::vector<std::vector<double>> values) {
    int len = values[0].size();
    for (int i = 0; i < values.size(); ++i) {
        if (values[i].size() != len) {
            std::cerr << "Inhomogenous vector shapes\n";
            return;
            // throw std::logic_error("Inhomogenous vector shapes");
        }
    }
    shape.first = values.size();
    shape.second = len;
    memory = values;
}

Matrix& Matrix::operator= (Matrix& other) {
    shape = other.shape;
    memory = other.memory;
    return *this;
}

Matrix& Matrix::operator= (Matrix&& other) {
    shape = std::move(other.shape);
    memory = std::move(other.memory);
    return *this;
}

Matrix Matrix::operator- () {
    Matrix result(*this);
    for (int i = 0; i < shape.first; ++i) {
        for (int j = 0; j < shape.second; ++j) {
            result[i][j] = -result[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator+ (Matrix& other) {
    if (shape != other.shape) {
        std::cerr << "Dimension mismatch\n";
        return Matrix();
        // throw std::logic_error("Dimension mismatch");
    }
    Matrix result(shape, 0.0);
    for (int i = 0; i < shape.first; ++i) {
        for (int j = 0; j < shape.second; ++j) {
            result[i][j] = memory[i][j] + other[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator- (Matrix& other) {
    if (shape != other.shape) {
        std::cerr << "Dimension mismatch\n";
        return Matrix();
        // throw std::logic_error("Dimension mismatch");
    }
    Matrix result(shape, 0.0);
    for (int i = 0; i < shape.first; ++i) {
        for (int j = 0; j < shape.second; ++j) {
            result[i][j] = memory[i][j] - other[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator* (Matrix& other) {
    if (shape.second != other.shape.first) {
        std::cerr << "Dimension mismatch\n";
        return Matrix();
        // throw std::logic_error("Dimension mismatch");
    }
    Matrix result(std::make_pair(shape.first, other.shape.second), 0.0);
    for (int i = 0; i < shape.first; ++i) {
        for (int j = 0; j < other.shape.second; ++j) {
            for (int k = 0; k < shape.second; ++k) {
                result[i][j] += memory[i][k] * other[k][j];
            }
        }
    }
    return result;
}

Matrix Matrix::augment(Matrix& other) {
    if (shape.first != other.shape.first) {
        std::cerr << "Dimension mismatch\n";
        return Matrix();
        // throw std::logic_error("Dimension mismatch");
    }
    Matrix result(std::make_pair(shape.first, shape.second + other.shape.second), 0.0);
    for (int i = 0; i < shape.first; ++i) {
        for (int j = 0; j < shape.second; ++j) {
            result[i][j] = memory[i][j];
        }
        for (int j = 0; j < other.shape.second; ++j) {
            result[i][j + shape.second] = other[i][j];
        }
    }
    return result;
}

Matrix Matrix::transpose() {
    Matrix result(std::make_pair(shape.second, shape.first), 0.0);
    for (int i = 0; i < shape.first; ++i) {
        for (int j = 0; j < shape.second; ++j) {
            result[j][i] = memory[i][j];
        }
    }
    return result;
}

Matrix Matrix::rref() {
    Matrix result(*this);
    int pi = 0, pj = 0;
    bool zero = true;
    std::vector<std::pair<int, int>> pivot_points;
    while (pi < shape.first and pj < shape.second) {
        if (result[pi][pj] == 0) {
            zero = true;
            for (int i = pi + 1; i < shape.first; ++i) {
                if (result[i][pj] != 0) {
                    result.swap_row(pi, i);
                    zero = false;
                    break;
                }
            }
            if (zero) {
                ++pj;
                continue;
            }
        }
        pivot_points.push_back(std::make_pair(pi, pj));
        result.row_operation(pi, {{pi, 1 / result[pi][pj]}});
        for (int i = pi + 1; i < shape.first; ++i) {
            if (result[i][pj] != 0) {
                result.row_operation(i, {
                    {i, 1},
                    {pi, -result[i][pj] / result[pi][pj]}
                });
            }
        }
        ++pi;
        ++pj;
    }
    for (std::vector<std::pair<int, int>>::reverse_iterator it = pivot_points.rbegin(); 
         it != pivot_points.rend(); 
         ++it) {
        std::pair<int, int> point = *it;
        pi = point.first;
        pj = point.second;
        result.row_operation(pi, {{pi, 1 / result[pi][pj]}});
        for (int i = pi - 1; i >= 0; --i) {
            if (result[i][pj] != 0) {
                result.row_operation(i, {
                    {i, 1},
                    {pi, -result[i][pj] / result[pi][pj]}
                });
            }
        }
    }
    return result;
}

Matrix Matrix::inverse(bool check_det) {
    if (shape.first != shape.second) {
        std::cerr << "Dimension mismatch\n";
        return Matrix();
        // throw std::logic_error("Nonsquare matrix does not have an inverse");
    }
    if (check_det) {
        if (fabs(determinant()) < 1e-7) {
            std::cerr << "Singular matrix does not have an inverse\n";
            return Matrix();
            // throw std::domain_error("Singular matrix does not have an inverse");
        }
    }
    Matrix id = identity(shape.first);
    Matrix aug = augment(id);
    Matrix reduced = aug.rref();
    Matrix result(std::make_pair(shape.first, shape.second), 0.0);
    for (int i = 0; i < shape.first; ++i) {
        for (int j = 0; j < shape.second; ++j) {
            result[i][j] = reduced[i][j + shape.second];
        }
    }
    return result;
}

Matrix Matrix::operator* (double scalar) {
    Matrix result(*this);
    for (int i = 0; i < shape.first; ++i) {
        for (int j = 0; j < shape.second; ++j) {
            result[i][j] *= scalar;
        }
    }
    return result;
}

Matrix Matrix::operator/ (double scalar) {
    Matrix result(*this);
    for (int i = 0; i < shape.first; ++i) {
        for (int j = 0; j < shape.second; ++j) {
            result[i][j] /= scalar;
        }
    }
    return result;
}

double Matrix::determinant() {
    if (shape.first != shape.second) {
        std::cerr << "Nonsquare matrix does not have a determinant\n";
        return nan("");
        // throw std::logic_error("Nonsquare matrix does not have a determinant");
    }
    Matrix result(*this);
    int pi = 0, pj = 0;
    int n_swaps = 0;
    bool zero = true;
    while (pi < shape.first and pj < shape.second) {
        if (result[pi][pj] == 0) {
            zero = true;
            for (int i = pi + 1; i < shape.first; ++i) {
                if (result[i][pj] != 0) {
                    ++n_swaps;
                    result.swap_row(pi, i);
                    zero = false;
                    break;
                }
            }
            if (zero) {
                ++pj;
                continue;
            }
        }
        for (int i = pi + 1; i < shape.first; ++i) {
            if (result[i][pj] != 0) {
                result.row_operation(i, {
                    {i, 1},
                    {pi, -result[i][pj] / result[pi][pj]}
                });
            }
        }
        ++pi;
        ++pj;
    }
    double det = result[0][0];
    for (int i = 1; i < shape.first; ++i) {
        det *= result[i][i];
    }
    if (n_swaps % 2 == 1) {
        return -det;
    }
    return det;
}

std::ostream& operator<< (std::ostream& os, Matrix& M) {
    os << "Matrix shape (" << M.shape.first << ", " << M.shape.second << ")\n";
    for (auto row : M.memory) {
        for (int j = 0; j < M.shape.second; ++j) {
            os << row[j] << (j == M.shape.second - 1 ? '\n' : ' ');
        }
    }
    return os;
}

std::ostream& operator<< (std::ostream& os, Matrix&& M) {
    os << "Matrix shape (" << M.shape.first << ", " << M.shape.second << ")\n";
    for (auto row : M.memory) {
        for (int j = 0; j < M.shape.second; ++j) {
            os << row[j] << (j == M.shape.second - 1 ? '\n' : ' ');
        }
    }
    return os;
}

Matrix identity(int n) {
    Matrix result(std::make_pair(n, n), 0.0);
    for (int i = 0; i < n; ++i) {
        result[i][i] = 1.0;
    }
    return result;
}