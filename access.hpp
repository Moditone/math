//
//  access.hpp
//  Math
//
//  Copyright © 2015-2016 Dsperados (info@dsperados.com). All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef DSPERADOS_MATH_ACCESS_HPP
#define DSPERADOS_MATH_ACCESS_HPP

#include <iterator>
#include <stdexcept>

#include "utility.hpp"

namespace math
{
    //! Lambda throwing when accessing outside of range
    static const auto throwAccess = [](auto begin, auto end, std::ptrdiff_t index)
    {
        if (index < 0 || index >= std::distance(begin, end))
            throw std::out_of_range("accessing out of the iterator range");
        
        return *std::next(begin, index);
    };
    
    //! Generates lamdba returning a constant value when accessing outside of a range
    template <typename T>
    inline const auto constantAccess(const T& constant)
    {
        return [constant](auto begin, auto end, std::ptrdiff_t index) -> typename decltype(begin)::value_type
        {
            if (index < 0 || index >= std::distance(begin, end))
                return constant;
            
            return *std::next(begin, index);
        };
    }
    
    //! Lambda clamping index when accessing outside of range
    static const auto clampAccess = [](auto begin, auto end, std::ptrdiff_t index)
    {
        return *std::next(begin, clamp<std::ptrdiff_t>(index, 0, std::distance(begin, end) - 1));
    };
    
    //! Lambda wrapping index when accessing outside of range
    static const auto wrapAccess = [](auto begin, auto end, std::ptrdiff_t index)
    {
        return *std::next(begin, wrap<std::ptrdiff_t>(index, std::distance(begin, end)));
    };
    
    //! Lambda mirroring index when accessing outside of range
    static const auto mirrorAccess = [](auto begin, auto end, std::ptrdiff_t index)
    {
        std::ptrdiff_t size = std::distance(begin, end);
        
        while (index < 0 || index >= size)
            index = (index < 0) ? -index : static_cast<std::ptrdiff_t>(2 * size - index - 2);
        
        return *std::next(begin, index);
    };
    
    //! Access element in a range, taking an accessor for out-of-range handling
    template <typename InputIterator, typename Accessor>
    auto access(InputIterator begin, InputIterator end, std::ptrdiff_t index, Accessor accessor)
    {
        return accessor(begin, end, index);
    }
}

#endif
