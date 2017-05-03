//
//  cross.hpp
//  Math
//
//  Copyright © 2015-2017 Dsperados (info@dsperados.com). All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef MATH_LINEAR_CROSS_HPP
#define MATH_LINEAR_CROSS_HPP

#include "vector.hpp"

namespace math
{
    //! Compute the cross product between two 2d vectors
    template <typename T1, typename T2>
    auto cross(const Vector2<T1>& lhs, const Vector2<T2>& rhs)
    {
        return lhs.x * rhs.y - lhs.y * rhs.x;
    }

    //! Compute the cross product between two 3d vectors
    template <typename T1, typename T2>
    auto cross(const Vector3<T1>& lhs, const Vector3<T2>& rhs)
    {
        Vector3<std::common_type_t<T1, T2>> result;
        
        result.x = lhs.y * rhs.z - lhs.z * rhs.y;
        result.y = lhs.z * rhs.x - lhs.x * rhs.z;
        result.z = lhs.x * rhs.y - lhs.y * rhs.x;
        
        return result;
    }
}

#endif /* MATH_LINEAR_CROSS_HPP */
