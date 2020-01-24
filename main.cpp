#include "matrix.h"

#include <iostream>

using namespace std;

int main() {
    const int DefaultValue = 0;
    const int MatrixSize = 10;

    Matrix<int, DefaultValue> matrix;

    // Запонение диагоналей матрицы
    for (int i = 0; i < MatrixSize; ++i)
        matrix(i, i) = matrix(MatrixSize - 1 - i, i) = i;

    // Заполнение матрицы в шахматном порядке значениями по умолчанию
    for (int row = 0; row < MatrixSize; row += 2)
        for (int col = 0; col < MatrixSize; col += 2)
            matrix(row + 1, col + 1) = matrix(row, col) = DefaultValue;

    for (int row = 1; row <= 8; ++row) {
        for (int col = 1; col <= 8; ++col)
            cout << matrix(row, col) << " ";
        cout << endl;
    }

    cout << "size = " << matrix.size() << endl;

    for (auto matrixValue : matrix) {
        auto dimension = matrixValue.first;
        auto value = matrixValue.second;

        std::string text;
        for (auto dimensionValue : dimension)
            text += std::to_string(dimensionValue) +", ";
        text = text.substr(0, text.length() - 2);

        std::cout << "(" << text << ") = " << value << endl;
    }

    return 0;
}
