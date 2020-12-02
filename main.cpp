#pragma once

#include "Matrix.h"
#include <iostream>
#include <string>
#include <chrono>
#include "cblas.h"
#include <fstream>

int main()
{
    const int dim = 10000;
    std::ofstream metrics;
    metrics.open("metrics-" + std::to_string(dim) + ".txt");
    std::cout.precision(15);
    metrics << std::setprecision(15);

    
    auto m1 = generateRandomMatrix(dim, dim);
    auto m2 = generateRandomMatrix(dim, dim);
    auto start = std::chrono::high_resolution_clock::now();
    auto m3 = m1 * m2;
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    metrics << "Time to multiply matrices with size: " << std::setw(4)
        << dim << "x" << dim << " doubles : " << diff.count() << " s\n";
    // m1.print();
    // m2.print();
    // m3.print();

    Matrix<double> m4(dim, dim);
    start = std::chrono::high_resolution_clock::now();
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, dim, dim, dim,
        1.0, m1._getInternalArray().data(), dim, m2._getInternalArray().data(), dim,
        0.0, m4._getInternalArray().data(), dim);
    end = std::chrono::high_resolution_clock::now();
    diff = end - start;
    metrics << "Time for BLAS to multiply matrices with size: " << std::setw(4)
        << dim <<"x"<<dim<< " doubles : " << diff.count() << " s\n";
    // m4.print();
    metrics << "result matrices comprasion (m3 == m4): " << (m3 == m4) << "\n";
    metrics.close();
    system("pause");
    return 0;
}