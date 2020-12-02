#ifndef  MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
#include <string>
#include <math.h>
#include <random>
#include <chrono>
#include <iomanip>

template <typename T>
class Matrix
{
private:
    int _rows;
    int _cols;
    std::vector<T> _mat;
    bool _equal(double a, double b)
    {
        return abs(a - b) < 1e-5;
    }
    bool _equal(int a, int b)
    {
        return a == b;
    }
    int _index(int r, int c)
    {
        return r * this->_cols + c;
    }

public:
    Matrix(const unsigned int rows, const unsigned int cols) : _rows(rows), _cols(cols), _mat(rows * cols, 0){};
    ~Matrix() = default;

    std::vector<T>& _getInternalArray()
    {
        return this->_mat;
    }

    T &operator()(const unsigned int r, const unsigned int c)
    {
        if (_index(r, c) > this->_rows * this->_cols)
        {
            throw std::out_of_range("Matrix index out of range");
        }
        return this->_mat[_index(r, c)];
    }
    void print()
    {
        std::cout << "Matrix: " << this->_rows << " " << this->_cols << "\n";
        for (int i = 0; i < this->_rows; ++i)
        {
            for (int j = 0; j < this->_cols; ++j)
                std::cout << std::setw(20) << this->_mat[_index(i, j)];
            std::cout << "\n";
        }
        std::cout << "---------------------------------------------------------------\n\n";
    }
    bool operator==(const Matrix &Mat)
    {
        if (this->_mat.size() != Mat._mat.size())
            return false;
        for (int i = 0; i < this->_mat.size(); ++i)
        {
            if (!this->_equal(this->_mat[i], Mat._mat[i]))
                return false;
        }
        return true;
    }
    Matrix operator*(const Matrix &Mat)
    {
        if (this->_cols != Mat._rows)
            throw std::invalid_argument("wrong matrix dimensions");
        Matrix m(this->_rows, Mat._cols);
        for (int i = 0; i < this->_rows; ++i)
            for (int j = 0; j < Mat._cols; ++j)
                for (int k = 0; k < this->_cols; ++k)
                    m(i, j) += this->_mat[_index(i, k)] * Mat._mat[_index(k, j)];
        return m;
    }
};

Matrix<double> generateIdentityMatrix(const unsigned int size)
{
    Matrix<double> m(size, size);
    for (int row = 0; row < size; ++row)
    {
        for (int col = 0; col < size; ++col)
        {
            m(row, col) = (row == col) ? 1 : 0;
        }
    }
    return m;
}

Matrix<double> generateRandomMatrix(const unsigned int rows, const unsigned int cols)
{
    Matrix<double> m(rows, cols);
    double lower_bound = -100;
    double upper_bound = 100;
    std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
    std::default_random_engine re;
    re.seed(std::chrono::system_clock::now().time_since_epoch().count());
    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            m(row, col) = unif(re);
        }
    }
    return m;
}
#endif // ! MATRIX_H