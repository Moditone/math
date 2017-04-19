//
//  trace.hpp
//  Math
//
//  Copyright © 2015-2017 Dsperados (info@dsperados.com). All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef MATH_LINEAR_TRACE_HPP
#define MATH_LINEAR_TRACE_HPP

#include "matrix.hpp"

namespace math
{
    //! Return the trace of a square matrix (accumulation of its diagonal)
    template <typename T, std::size_t N>
    auto trace(const Matrix<T, N, N>& matrix)
    {
        T y = 0;
        for (auto i = 0; i < N; ++i)
            y += matrix[i][i];
        return y;
    }
}

#endif