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
    using AccessorFunction = std::function<typename std::iterator_traits<Iterator>::value_type(Iterator, Iterator, std::ptrdiff_t)>;

// --- Accessor lambda's --- //

    //! Lambda throwing when accessing outside of range
    template <typename Iterator>
    auto accessThrowing(Iterator begin, Iterator end, std::ptrdiff_t index) -> typename std::iterator_traits<Iterator>::reference
    {
        if (index < 0 || index >= std::distance(begin, end))
            throw std::out_of_range("accessing out of the iterator range");
        
        return *std::next(begin, index);
    };
    
    template <typename Iterator, typename Constant>
    auto accessConstant(Iterator begin, Iterator end, std::ptrdiff_t index, const Constant& constant) ->
        typename std::common_type<typename std::iterator_traits<Iterator>::reference, Constant>::type
    {
        if (index < 0 || index >= std::distance(begin, end))
            return constant;
        
        return *std::next(begin, index);
    }
    
    //! Lambda clamping index when accessing outside of range
	template <typename Iterator>
    auto accessClamped(Iterator begin, Iterator end, std::ptrdiff_t index) -> typename std::iterator_traits<Iterator>::reference
    {
        return *std::next(begin, clamp<std::ptrdiff_t>(index, 0, std::distance(begin, end) - 1));
    };
    
    //! Lambda wrapping index when accessing outside of range
	template <typename Iterator>
    auto accessWrapped(Iterator begin, Iterator end, std::ptrdiff_t index) -> typename std::iterator_traits<Iterator>::reference
    {
        return *std::next(begin, wrap<std::ptrdiff_t>(index, std::distance(begin, end)));
    };
    
    //! Lambda mirroring index when accessing outside of range
    template <typename Iterator>
    auto accessMirrored(Iterator begin, Iterator end, std::ptrdiff_t index) -> typename std::iterator_traits<Iterator>::reference
    {
        std::ptrdiff_t size = std::distance(begin, end);
        
        while (index < 0 || index >= size)
            index = (index < 0) ? -index : static_cast<std::ptrdiff_t>(2 * size - index - 2);
        
        return *std::next(begin, index);
    };
}

#endif
