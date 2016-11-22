//
//  access.hpp
//  Math
//
//  Created by Stijn Frishert (info@stijnfrishert.com) on 16/05/2016.
//  Copyright © 2015-2016 Stijn Frishert. All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef DSPERADOS_MATH_ACCESS_HPP
#define DSPERADOS_MATH_ACCESS_HPP

#include <iterator>
#include <stdexcept>

#include "utility.hpp"

namespace math
{
    //! Function object for clamped range access
    /*! Clamps index before accessing a range */
    struct ThrowAccess
    {
        template <class InputIterator, class Index>
        constexpr typename InputIterator::value_type operator()(InputIterator begin, InputIterator end, Index index) const
        {
            if (index < 0 || index >= std::distance(begin, end))
                throw std::out_of_range("Accessing out of the iterator range");
            
            return *std::next(begin, index);
        }
    };

    //! Function object for range access with a fixed constant out of range
    /*! Returns a given fixed constant when accessing out of the iterator range */
    template <class T>
    struct ConstantAccess
    {
        ConstantAccess(const T& value = T{}) : value(value) { }
        
        template <class InputIterator, class Index>
        constexpr typename InputIterator::value_type operator()(InputIterator begin, InputIterator end, Index index) const
        {
            if (index < 0 || index >= std::distance(begin, end))
                return value;
            
            return *std::next(begin, index);
        }
        
        T value;
    };
    
    //! Function object for clamped range access
    /*! Clamps index before accessing a range
        @warning If begin == end, the result is undefined */
    struct ClampedAccess
    {
        template <class InputIterator, class Index>
        constexpr auto operator()(InputIterator begin, InputIterator end, Index index) const
        {
            return *std::next(begin, clamp<std::ptrdiff_t>(index, 0, std::distance(begin, end) - 1));
        }
    };
    
    //! Function object for wrapped range access
    /*! Wraps index before accessing a range
        @warning If begin == end, the result is undefined */
    struct WrappedAccess
    {
        template <class InputIterator, class Index>
        constexpr auto operator()(InputIterator begin, InputIterator end, Index index) const
        {
            return *std::next(begin, wrap(index, std::distance(begin, end)));
        }
    };
    
    //! Function object for mirrored range access
    /*! Mirrors index before accessing a range
        @warning If begin == end, the result is undefined */
    struct MirroredAccess
    {
        template <class InputIterator, class Index>
        constexpr auto operator()(InputIterator begin, InputIterator end, Index index) const
        {
            std::ptrdiff_t size = std::distance(begin, end);
            
            while (index < 0 || index >= size)
                index = (index < 0) ? -index : static_cast<Index>(2 * size - index - 2);
            
            return *std::next(begin, index);
        }
    };
    
    //! Access element in a range, taking an accessor for out-of-range handling
    template <class InputIterator, class Index, class Accessor = ThrowAccess>
    auto access(InputIterator begin, InputIterator end, Index index, Accessor accessor = Accessor())
    {
        return accessor(begin, end, index);
    }
}

#endif
