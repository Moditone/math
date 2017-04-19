//
//  inverse.hpp
//  Math
//
//  Copyright © 2015-2017 Dsperados (info@dsperados.com). All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef MATH_LINEAR_INVERSE_HPP
#define MATH_LINEAR_INVERSE_HPP

#include "determinant.hpp"
#include "matrix.hpp"

namespace math
{
    template <typename T>
    Matrix2<T> invert(const Matrix2<T>& mat)
    {
        auto d = determinant(mat);
        if (d == 0)
            throw std::runtime_error("matrix with determinant of 0 doesn't have an inverse");

        const T dr = 1.0 / d;
        return {{mat[1][1] * dr, -mat[0][1] * dr}, {-mat[1][0] * dr, mat[0][0] * dr}};
    }
}

#endif /* MATH_LINEAR_INVERSE_HPP */
