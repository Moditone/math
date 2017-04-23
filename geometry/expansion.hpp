//
//  expansion.hpp
//  Math
//
//  Copyright © 2015-2017 Dsperados (info@dsperados.com). All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef MATH_GEOMETRY_EXPANSION_HPP
#define MATH_GEOMETRY_EXPANSION_HPP

#include "rectangular.hpp"
#include "size.hpp"

namespace math
{
    //! Expand a rectangular
    /*! @relates Rectangular */
    template <class T, std::size_t N, class U>
    auto expand(const Rectangular<T, N>& rect, const Size<U, N>& expansion)
    {
        Rectangular<std::common_type_t<T, U>, N> result = rect;
        
        for (auto i = 0; i < N; ++i)
        {
            if (result.size[i] < 0)
            {
                result.origin[i] += expansion[i];
                result.size[i] -= expansion[i] * 2;
            } else {
                result.origin[i] -= expansion[i];
                result.size[i] += expansion[i] * 2;
            }
        }
        
        return result;
    }

    //! Expand a rectangular to contain a point
    /*! @relates Rectangular */
    template <class T, class U, std::size_t N>
    auto expand(const Rectangular<T, N>& rect, const Vector<U, N>& point)
    {
        Rectangular<std::common_type_t<T, U>, N> result;

        for (auto n = 0; n < N; ++n)
        {
            result.origin[n] = std::min(point[n], rect.origin[n]);
            result.origin[n] = std::max(point[n], rect.origin[n] + rect.size[n]) - result.origin[n];
        }

        return result;
    }

    //! Expand a rectangular to contain another
    /*! @relates Rectangular */
    template <class T, class U, std::size_t N>
    auto expand(const Rectangular<T, N>& rect, const Rectangular<U, N>& rhs)
    {
        return expand(expand(rect, rhs.origin), rhs.outer());
    }

        //! Expand a rectangle
    /*! @relates Rectangular */
    template <class T, class U, class V>
    auto expand(const Rectangular<T, 2>& rect, const U& horizontal, const V& vertical)
    {
        return expand(rect, Size2<std::common_type_t<U, V>>(horizontal, vertical));
    }
}

#endif /* MATH_GEOMETRY_EXPANSION_HPP */
