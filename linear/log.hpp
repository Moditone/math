//
//  log.hpp
//  Math
//
//  Copyright © 2015-2017 Dsperados (info@dsperados.com). All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef MATH_LINEAR_LOG_HPP
#define MATH_LINEAR_LOG_HPP

#include <cmath>

#include "vector.hpp"

namespace math
{
	//! Compute the absolute value of a vector
    template <typename T, std::size_t N>
    auto log(const Vector<T, N>& vector)
    {
        Vector<T, N> result;
        for(auto i = 0; i < N; i++)
            result[i] = std::log(vector[i]);
        
        return result;
    }
}

namespace std
{
    template <typename T, std::size_t N>
    auto log(const math::Vector<T, N>& vector)
    {
        return math::log(vector);
    }
}

#endif /* MATH_LINEAR_ABSOLUTE_HPP */
