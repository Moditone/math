//
//  access.hpp
//  Math
//
//  Copyright © 2015-2017 Dsperados (info@dsperados.com). All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef DSPERADOS_MATH_ACCESS_HPP
#define DSPERADOS_MATH_ACCESS_HPP

#include <cstddef>
#include <functional>
#include <iterator>
#include <stdexcept>
#include <type_traits>

#include "clamp.hpp"
#include "wrap.hpp"

namespace math
{
    //! Functors for storing accessors
    template <typename Iterator>
    using AccessorFunction = std::function<std::decay_t<decltype(*std::declval<Iterator>())>(Iterator, Iterator, std::ptrdiff_t)>;

// --- Accessor lambda's --- //

    //! Lambda throwing when accessing outside of range
    static const auto throwAccess = [](auto begin, auto end, std::ptrdiff_t index) -> typename std::iterator_traits<decltype(begin)>::reference
    {
        if (index < 0 || index >= std::distance(begin, end))
            throw std::out_of_range("accessing out of the iterator range");
        
        return *std::next(begin, index);
    };
    
    //! Generates lamdba returning a constant value when accessing outside of a range
    template <typename T>
    const auto constantAccess(const T& constant)
    {
        return [constant](auto begin, auto end, std::ptrdiff_t index) -> typename std::iterator_traits<decltype(begin)>::value_type
        {
            if (index < 0 || index >= std::distance(begin, end))
                return constant;
            
            return *std::next(begin, index);
        };
    }
    
    //! Lambda clamping index when accessing outside of range
    static const auto clampAccess = [](auto begin, auto end, std::ptrdiff_t index) -> typename std::iterator_traits<decltype(begin)>::reference
    {
        return *std::next(begin, clamp<std::ptrdiff_t>(index, 0, std::distance(begin, end) - 1));
    };
    
    //! Lambda wrapping index when accessing outside of range
    static const auto wrapAccess = [](auto begin, auto end, std::ptrdiff_t index) -> typename std::iterator_traits<decltype(begin)>::reference
    {
        return *std::next(begin, wrap<std::ptrdiff_t>(index, std::distance(begin, end)));
    };
    
    //! Lambda mirroring index when accessing outside of range
    static const auto mirrorAccess = [](auto begin, auto end, std::ptrdiff_t index) -> typename std::iterator_traits<decltype(begin)>::reference
    {
        std::ptrdiff_t size = std::distance(begin, end);
        
        while (index < 0 || index >= size)
            index = (index < 0) ? -index : static_cast<std::ptrdiff_t>(2 * size - index - 2);
        
        return *std::next(begin, index);
    };
}

#endif
