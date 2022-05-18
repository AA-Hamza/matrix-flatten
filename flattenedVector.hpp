#ifndef FLATTENEDVECTOR_H
#define FLATTENEDVECTOR_H

#include <iostream>
#include <vector>

template <typename T> class flattenedVector
{
  public:
    // Constructors
    flattenedVector<T>() : n(0), m(0), p(0), q(0)
    {
    }

    flattenedVector<T>(std::size_t n, std::size_t m, std::size_t p) : n(n), m(m), p(p), q(n * m * p)
    {
        array1D.reserve(q);
    }

    flattenedVector<T>(const std::vector<std::vector<std::vector<T>>> &matrix3D)
    {
        *this = matrix3D;
    }

    // Operator Overloads
    flattenedVector<T> &operator=(const std::vector<std::vector<std::vector<T>>> &matrix3D)
    {
        n = matrix3D.size();
        m = matrix3D[0].size();
        p = matrix3D[0][0].size();
        q = n * m * p;
        array1D.reserve(q);
        std::size_t myIndex = 0;
        for (std::size_t i = 0; i < n; ++i)
        {
            for (std::size_t j = 0; j < m; ++j)
            {
                std::copy(matrix3D[i][j].begin(), matrix3D[i][j].end(), array1D.begin() + myIndex);
                myIndex += p;
            }
        }
        return *this;
    }

    T &operator[](const std::size_t index)
    {
        return array1D[index];
    }

    // at function to access it like a 3D matrix
    T &at(std::size_t i, std::size_t j, std::size_t k)
    {
        return array1D[i * (m * p) + j * (p) + k];
    }

    // Destructor
    ~flattenedVector()
    {
    }

  private:
    std::size_t n, m, p, q;
    std::vector<T> array1D;
};

#endif
