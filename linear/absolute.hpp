//
//  absolute.hpp
//  Math
//
//  Copyright © 2015-2017 Dsperados (info@dsperados.com). All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef MATH_LINEAR_ABSOLUTE_HPP
#define MATH_LINEAR_ABSOLUTE_HPP

#include <cmath>

#include "vector.hpp"

namespace math
{
	//! Compute the absolute value of a vector
    template <typename T, std::size_t N>
    auto abs(const Vector<T, N>& vector)
    {
        Vector<T, N> result;
        for(auto i = 0; i < N; i++)
            result[i] = std::fabs(vector[i]);
        
        return result;
    }
}

#endif /* MATH_LINEAR_ABSOLUTE_HPP */
