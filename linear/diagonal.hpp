//
//  diagonal.hpp
//  Math
//
//  Copyright © 2015-2017 Dsperados (info@dsperados.com). All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef MATH_LINEAR_DIAGONAL_HPP
#define MATH_LINEAR_DIAGONAL_HPP

#include "matrix.hpp"
#include "vector.hpp"

namespace math
{
    //! Return the diagonal of a square matrix as a vector
    template <typename T, std::size_t N>
    auto diagonal(const Matrix<T, N, N>& matrix)
    {
        Vector<T, N> d;
        for (auto i = 0; i < N; ++i)
            d[i] = matrix[i][i];
        return d;
    }
}

#endif