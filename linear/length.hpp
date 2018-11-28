//
//  length.hpp
//  Math
//
//  Copyright © 2015-2017 Dsperados (info@dsperados.com). All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef MATH_LINEAR_LENGTH_HPP
#define MATH_LINEAR_LENGTH_HPP

#include <numeric>
#include <cmath>

#include "vector.hpp"

namespace math
{
    template <typename T>
    T length(const T& scalar)
    {
        return scalar;
    }
    
    template <typename T, std::size_t N>
    auto length(const Vector<T, N>& vector)
    {
        T acc = 0;
        for (auto& element : vector)
            acc += element * element;
        return std::sqrt(acc);
    }

    template <typename T>
    T length(const Vector2<T>& vector)
    {
        return std::sqrt(vector.x * vector.x + vector.y * vector.y);
    }
    
    template <typename T>
    T length(const Vector3<T>& vector)
    {
        return std::sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
    }
    
    template <typename T>
    T length(const Vector4<T>& vector)
    {
        return std::sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z + vector.w * vector.w);
    }
}

#endif /* MATH_LINEAR_LENGTH_HPP */
