//
//  determinant.hpp
//  Math
//
//  Copyright © 2015-2017 Dsperados (info@dsperados.com). All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef MATH_LINEAR_DETERMINANT_HPP
#define MATH_LINEAR_DETERMINANT_HPP

#include "matrix.hpp"

namespace math
{
    //! Compute the determinant of a 2d matrix
    template <typename T>
    auto determinant(const Matrix2<T>& matrix)
    {
        return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
    }

    //! Compute the determinant of a 3d matrix
    template <typename T>
    auto determinant(const Matrix3<T>& matrix)
    {
        return matrix[0][0] * matrix[1][1] * matrix[2][2] +
               matrix[0][1] * matrix[1][2] * matrix[2][0] +
               matrix[0][2] * matrix[1][0] * matrix[2][1] -
               matrix[0][0] * matrix[1][2] * matrix[2][1] -
               matrix[0][1] * matrix[1][0] * matrix[2][2] -
               matrix[0][2] * matrix[1][1] * matrix[2][0];
    }
}

#endif