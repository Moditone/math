//
//  intersection.hpp
//  Math
//
//  Copyright © 2015-2017 Dsperados (info@dsperados.com). All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef MATH_GEOMETRY_INTERSECTION_HPP
#define MATH_GEOMETRY_INTERSECTION_HPP

#include "rectangular.hpp"
#include "size.hpp"

namespace math
{
	//! Do two rectangulars intersect?
    /*! @relates Rectangular */
    template <class T, class U, std::size_t N>
    bool intersectsExclusive(const Rectangular<T, N>& rect1, const Rectangular<U, N>& rect2)
    {
        const auto r1 = normalize(rect1);
        const auto r2 = normalize(rect2);

        for (auto n = 0; n < N; ++n)
        {
            if (((r1.origin[n] < r2.origin[n]) || (r1.origin[n] >= r2.outer()[n])) &&
                ((r2.origin[n] < r1.origin[n]) || (r2.origin[n] >= r1.outer()[n])))
            {
                return false;
            }
        }

        return true;
    }

    //! Do two rectangulars intersect?
    /*! @relates Rectangular */
    template <class T, class U, std::size_t N>
    bool intersectsInclusive(const Rectangular<T, N>& rect1, const Rectangular<U, N>& rect2)
    {
        const auto r1 = normalize(rect1);
        const auto r2 = normalize(rect2);

        for (auto n = 0; n < N; ++n)
        {
            if (((r1.origin[n] < r2.origin[n]) || (r1.origin[n] > r2.outer()[n])) &&
                ((r2.origin[n] < r1.origin[n]) || (r2.origin[n] > r1.outer()[n])))
            {
                return false;
            }
        }

        return true;
    }

    //! The intersection of two rectangulars
    /*! The intersection is the rectangular that both lhs and rhs have in common
        @relates Rectangular */
    template <class T, class U, std::size_t N>
    Rectangular<T, N> intersect(const Rectangular<T, N>& lhs, const Rectangular<U, N>& rhs)
    {
        Rectangular<std::common_type_t<T, U>, N> intersection;
        for (auto i = 0; i < N; ++i)
        {
            intersection.origin[i] = std::max<T>(lhs.origin[i], rhs.origin[i]);
            intersection.size[i] = std::min<T>(lhs.origin[i] + lhs.size[i], rhs.origin[i] + rhs.size[i]) - intersection.origin[i];
        }

        return intersection;
    }
}

#endif /* MATH_GEOMETRY_INTERSECTION_HPP */
