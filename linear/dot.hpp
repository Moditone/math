//
//  dot.hpp
//  Math
//
//  Copyright © 2015-2017 Dsperados (info@dsperados.com). All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef MATH_LINEAR_DOT_HPP
#define MATH_LINEAR_DOT_HPP

#include <stdio.h>

#include "vector.hpp"

namespace math
{
    //! Take the dot product of two vectors
    template <typename T1, typename T2, std::size_t N>
    auto dot(const Vector<T1, N>& lhs, const Vector<T2, N>& rhs)
    {
        std::common_type_t<T1, T2> acc;
        for (auto i = 0; i < N; ++i)
            acc += lhs[i] * rhs[i];
        return acc;
    }

    //! Take the dot product of two 2d vectors
    template <typename T1, typename T2>
    auto dot(const Vector2<T1>& lhs, const Vector2<T2>& rhs)
    {
        return lhs.x * rhs.x + lhs.y * rhs.y;
    }
    
    //! Take the dot product of two 3d vectors
    template <typename T1, typename T2>
    auto dot(const Vector3<T1>& lhs, const Vector3<T2>& rhs)
    {
        return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
    }
    
    //! Take the dot product of two 4d vectors
    template <typename T1, typename T2>
    auto dot(const Vector4<T1>& lhs, const Vector4<T2>& rhs)
    {
        return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
    }

    //! Take the dot product of two containers
    template <class InputIterator1, class InputIterator2>
    auto dot(InputIterator1 begin1, std::size_t stride1, InputIterator2 begin2, std::size_t stride2, std::size_t size)
    {
        std::common_type_t<decltype(*begin1), decltype(*begin2)> out = {0};
        
        for (auto i = 0; i < size; ++i)
        {
            out += *begin1 * *begin2;
            begin1 += stride1;
            begin2 += stride2;
        }
        
        return out;
    }
    
    //! Take the dot product of two containers
    template <class InputIterator1, class InputIterator2>
    auto dot(InputIterator1 begin1, InputIterator2 begin2, std::size_t size)
    {
        return dot(begin1, 1, begin2, 1, size);
    }
}

#endif