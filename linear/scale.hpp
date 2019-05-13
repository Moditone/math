//
//  scale.hpp
//  Math
//
//  Copyright © 2015-2017 Dsperados (info@dsperados.com). All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef BEAR_GRAPHICS_SCALE_HPP
#define BEAR_GRAPHICS_SCALE_HPP

#include <moditone/math/linear/matrix.hpp>
#include <moditone/math/linear/vector.hpp>

namespace bear::graphics
{
    //! Create a scaling matrix
    template <typename T, std::size_t N>
    math::Matrix<T, N, N> scale(const math::Vector<T, N>& axis)
    {
        return math::Matrix<T, N, N>(axis);
    }
    
    //! Create a 3d scaling matrix
    template <typename T>
    math::Matrix3<T> scale3d(const T& x, const T& y, const T& z)
    {
        return math::Matrix3<T>(math::Vector3<T>{x, y, z});
    }
    
    //! Create a 4d scaling matrix
    template <typename T>
    math::Matrix4<T> scale4d(const T& x, const T& y, const T& z)
    {
        return math::Matrix4<T>(math::Vector4<T>{x, y, z, 1});
    }
}

#endif

