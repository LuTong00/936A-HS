#ifndef TEST_MATRIX_HPP
#define TEST_MATRIX_HPP

#include <pathing/matrix.hpp>

#define print(x) do {std::cout << #x << ":\n" << x << "\n\n";} while(0);

void test_matrix() {
    Matrix default_constructor;
    print(default_constructor);

    Matrix shape_value({2, 3}, 3.1);
    print(shape_value);

    double arr_values[] = {4.1, 5.9, 2.6, 5.3, 5.8, 9.7};
    Matrix shape_values({2, 3}, arr_values);
    print(shape_values);

    std::vector<std::vector<double>> vector_values(2, std::vector<double>(3, 9.3));
    Matrix vector(vector_values);
    print(vector);

    Matrix copy_constructor(shape_value);
    print(copy_constructor);
    copy_constructor[0][1] = 2.3;
    std::cout << "After modification:\n";
    print(copy_constructor);
    std::cout << "Original:\n";
    print(shape_value);

    Matrix move_constructor(std::move(shape_values));
    print(move_constructor);
    print(shape_values);

    Matrix to_rref(std::vector<std::vector<double>>({{1, 1, 1, -6}, {4, 2, 1, -10}, {9, 3, 1, -20}}));
    print(to_rref.rref());

    Matrix to_be_inverted(std::vector<std::vector<double>>({{1, 2, 3}, {4, 5, 6}, {7, 9, 8}}));
    Matrix inverse = to_be_inverted.inverse();
    print(inverse);
    print(to_be_inverted * inverse);
    print(inverse.determinant());
    print(to_be_inverted.determinant());

    Matrix identity_matrix = identity(3);
    print(identity_matrix);
}

#undef print

#endif