//
//  transpose.hpp
//  Math
//
//  Copyright © 2015-2017 Dsperados (info@dsperados.com). All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef MATH_LINEAR_TRANSPOSE_HPP
#define MATH_LINEAR_TRANSPOSE_HPP

#include "matrix.hpp"

namespace math
{
    //! Tranpose a matrix (swap columns and rows)
    template <typename T, std::size_t C, std::size_t R>
    auto transpose(const Matrix<T, C, R>& matrix)
    {
        Matrix<T, R, C> mat;
        
        for (auto c = 0; c < C; ++c)
        {
            for (auto r = 0; r < R; ++r)
                mat[r][c] = matrix[c][r];
        }

        return mat;
    }
}

#endif