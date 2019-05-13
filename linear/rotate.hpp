//
//  rotate.hpp
//  Math
//
//  Copyright © 2015-2017 Dsperados (info@dsperados.com). All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef BEAR_GRAPHICS_ROTATE_HPP
#define BEAR_GRAPHICS_ROTATE_HPP

#include <cmath>

#include <moditone/math/linear/matrix.hpp>
#include <moditone/math/linear/normalize.hpp>

namespace bear::graphics
{
    //! Create a 2d rotation matrix
    template <typename T>
    math::Matrix2<T> rotation2d(float angle)
    {
        const auto s = std::sin(angle);
        const auto c = std::cos(angle);

        return {{ c, s }, { -s, c }};
    }

    //! Create a 3d rotation matrix
    template <typename T>
    math::Matrix3<T> rotation3dOverX(float angle)
    {
        const auto s = std::sin(angle);
        const auto c = std::cos(angle);

        return {{1, 0, 0}, {0, c, -s}, {0, s, c}};
    }
    
    //! Create a 4d rotation matrix
    template <typename T>
    math::Matrix4<T> rotation4dOverX(float angle)
    {
        const auto s = std::sin(angle);
        const auto c = std::cos(angle);
        
        return {{1, 0, 0, 0}, {0, c, -s, 0}, {0, s, c, 0}, {0, 0, 0, 1}};
    }
    
    //! Create a 3d rotation matrix
    template <typename T>
    math::Matrix3<T> rotation3dOverY(float angle)
    {        
        const auto s = std::sin(angle);
        const auto c = std::cos(angle);

        return {{c, 0, s}, {0, 1, 0}, {-s, 0, c}};
    }
    
    //! Create a 4d rotation matrix
    template <typename T>
    math::Matrix4<T> rotation4dOverY(float angle)
    {
        const auto s = std::sin(angle);
        const auto c = std::cos(angle);
        
        return {{c, 0, s, 0}, {0, 1, 0, 0}, {-s, 0, c, 0}, {0, 0, 0, 1}};
    }
    
    //! Create a 3d rotation matrix
    template <typename T>
    math::Matrix3<T> rotation3dOverZ(float angle)
    {        
        const auto s = std::sin(angle);
        const auto c = std::cos(angle);

        return {{c, -s, 0}, {s, c, 0}, {0, 0, 1}};
    }
    
    //! Create a 4d rotation matrix
    template <typename T>
    math::Matrix4<T> rotation4dOverZ(float angle)
    {
        const auto s = std::sin(angle);
        const auto c = std::cos(angle);
        
        return {{c, -s, 0, 0}, {s, c, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
    }

    //! Create 3d rotation matrix around an arbitrary axis
    template <typename T>
    math::Matrix3<T> rotation3d(const math::Vector3<T>& axis, float angle)
    {
        const auto s = std::sin(angle);
        const auto c = std::cos(angle);
        const auto q = 1 - c;

        const auto u = math::normalize(axis);

        const auto xy = u.x * u.y;
        const auto xz = u.x * u.z;
        const auto yz = u.y * u.z;

        return {{ c + u.x * u.x * q, xy * q + u.z * s, xz * q - u.y * s},
                { xy * q - u.z * s, c + u.y * u.y * q, yz * q + u.x * s},
                { xz * q + u.y * s, yz * q - u.x * s, c + u.z * u.z * q}};
    }
    
    //! Create 4d rotation matrix around an arbitrary axis
    template <typename T>
    math::Matrix4<T> rotation4d(const math::Vector3<T>& axis, float angle)
    {
        const auto s = std::sin(angle);
        const auto c = std::cos(angle);
        const auto q = 1 - c;
        
        const auto u = math::normalize(axis);
        
        const auto xy = u.x * u.y;
        const auto xz = u.x * u.z;
        const auto yz = u.y * u.z;
        
        return {{ c + u.x * u.x * q, xy * q + u.z * s, xz * q - u.y * s, 0 },
                { xy * q - u.z * s, c + u.y * u.y * q, yz * q + u.x * s, 0 },
                { xz * q + u.y * s, yz * q - u.x * s, c + u.z * u.z * q, 0 },
                {0, 0, 0, 1}};
    }
}

#endif
