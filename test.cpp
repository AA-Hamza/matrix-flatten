#include "flattenedVector.hpp"
#include <iostream>
#include <random>
#include <vector>

// Aliasing 3D vectors, for better readability
template <typename T> using stlVector3D = std::vector<std::vector<std::vector<T>>>;

template <typename T> void populateMatrix(stlVector3D<T> &matrix3D)
{
    size_t n = matrix3D.size();
    size_t m = matrix3D[0].size();
    size_t p = matrix3D[0][0].size();
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < m; ++j)
        {
            for (size_t k = 0; k < p; ++k)
            {
                matrix3D[i][j][k] = rand();
            }
        }
    }
}

template <typename T> int assertEquals(stlVector3D<T> &matrix3D, flattenedVector<T> &flattened)
{
    size_t n = matrix3D.size();
    size_t m = matrix3D[0].size();
    size_t p = matrix3D[0][0].size();
    size_t flattendIndex = 0;
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < m; ++j)
        {
            for (size_t k = 0; k < p; ++k)
            {
                if (matrix3D[i][j][k] != flattened[flattendIndex] || matrix3D[i][j][k] != flattened.at(i, j, k))
                {
                    std::cout << "Assertion Failed at flattend[" << flattendIndex << "] = " << flattened[flattendIndex]
                              << std::endl;
                    std::cout << flattened[flattendIndex] << " != " << matrix3D[i][j][k] << std::endl;
                    return 0;
                }
                flattendIndex++;
            }
        }
    }
    return 1;
}

int main(int argc, char **argv)
{
    // Default value for the maximum length of each dimension
    size_t dimensionMax = 100;

    // Override the default dimensionMax
    if (argc == 2)
    {
        dimensionMax = atol(argv[1]);

        // Error
        if (dimensionMax == 0)
        {
            dimensionMax = 100;
        }
    }
    std::cout << "Testing with dimensionMax=" << dimensionMax << std::endl;

    size_t n = rand() % dimensionMax;
    size_t m = rand() % dimensionMax;
    size_t p = rand() % dimensionMax;

    // Initialize the 3D matrix
    stlVector3D<int> matrix3D(n, std::vector<std::vector<int>>(m, std::vector<int>(p)));

    // Populate the 3D matrix
    populateMatrix(matrix3D);

    flattenedVector<int> flattend(matrix3D);

    if (assertEquals(matrix3D, flattend))
    {
        std::cout << "TEST Passed" << std::endl;
        return 0;
    }
    else
    {
        std::cout << "TEST Failed" << std::endl;
        std::cout << "Exiting with -1..." << std::endl;
        return -1;
    }
}
