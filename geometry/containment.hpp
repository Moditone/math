//
//  containment.hpp
//  Math
//
//  Copyright © 2015-2017 Dsperados (info@dsperados.com). All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef MATH_GEOMETRY_CONTAINMENT_HPP
#define MATH_GEOMETRY_CONTAINMENT_HPP

#include "../linear/vector.hpp"
#include "circular.hpp"
#include "rectangular.hpp"

namespace math
{
	//! Does a rectangular contain a point?
    /*! @relates Rectangular */
    template <class T, class U, std::size_t N>
    bool containsExclusive(const Rectangular<T, N>& rect, const Vector<U, N>& point)
    {
        const auto r = normalize(rect);
        for (auto n = 0; n < N; ++n)
        {
            if (point[n] < r.origin[n] || r.outer()[n] <= point[n])
                return false;
        }
        
        return true;
    }

    //! Does a rectangular contain a point?
    /*! @relates Rectangular */
    template <class T, class U, std::size_t N>
    bool containsInclusive(const Rectangular<T, N>& rect, const Vector<U, N>& point)
    {
        const auto r = normalize(rect);
        for (auto n = 0; n < N; ++n)
        {
            if (point[n] < r.origin[n] || r.outer()[n] < point[n])
                return false;
        }

        return true;
    }
    
    //! Does a rectangular contain another?
    /*! @relates Rectangular */
    template <class T, class U, std::size_t N>
    bool containsExclusive(const Rectangular<T, N>& rect1, const Rectangular<U, N>& rect2)
    {
        return containsExclusive(rect1, rect2.origin) && containsExclusive(rect1, rect2.outer());
    }
    
    //! Does a rectangular contain another?
    /*! @relates Rectangular */
    template <class T, class U, std::size_t N>
    bool containsInclusive(const Rectangular<T, N>& rect1, const Rectangular<U, N>& rect2)
    {
        return containsInclusive(rect1, rect2.origin) && containsInclusive(rect1, rect2.outer());
    }

        //! Does a circular contain a point?
    /*! @relates Rectangular */
    template <class T, class U, std::size_t N>
    bool containsInclusive(const Circular<T, N>& circular, const Vector<U, N>& point)
    {
        std::common_type_t<T, U> acc = 0;
        for (auto n = 0; n < N; ++n)
        {
            const auto d = std::fabs(point[n] - circular.center[n]);
            acc += d * d;
        }
        
        return std::sqrt(acc) <= circular.radius;
    }
    
    //! Does a circular contain a point?
    /*! @relates Rectangular */
    template <class T, class U, std::size_t N>
    bool containsExclusive(const Circular<T, N>& circular, const Vector<U, N>& point)
    {
        std::common_type_t<T, U> acc = 0;
        for (auto n = 0; n < N; ++n)
        {
            const auto d = std::fabs(point[n] - circular.center[n]);
            acc += d * d;
        }
        
        return std::sqrt(acc) < circular.radius;
    }
}

#endif /* MATH_GEOMETRY_CONTAINMENT_HPP */
