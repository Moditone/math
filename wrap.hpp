//
//  wrap.hpp
//  Math
//
//  Created by Stijn on 07/08/2017.
//
//

#ifndef DSPERADOS_MATH_WRAP_HPP
#define DSPERADOS_MATH_WRAP_HPP

#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <type_traits>

namespace math
{
    //! Wrap a number within a given range
    /*! @throw std::invalid_argument if max <= min */
    template <typename T>
    std::enable_if_t<!std::is_integral<T>::value || std::is_signed<T>::value, T> wrap(T value, const T& min, const T& max)
    {
        if (max <= min)
            throw std::invalid_argument("max <= min");
        
        while (max <= value)
            value -= (max - min);
        
        while (value < min)
            value += (max - min);
        
        return value;
    }
    
    //! Wrap a number within a given range
    /*! @throw std::invalid_argument if max <= min */
    template <typename T>
    std::enable_if_t<std::is_unsigned<T>::value, T> wrap(T value, const T& min, const T& max)
    {
        using T2 = typename std::make_signed<T>::type;
        const auto& result = wrap<T2>(static_cast<T2>(value), static_cast<T2>(min), static_cast<T2>(max));
        return static_cast<T>(result);
    }
    
    //! Wrap a number within a given range, where min = 0
    /*! @throw std::invalid_argument if max <= 0 */
    template <typename T, typename U>
    auto wrap(T value, const U& max)
    {
        if (max <= 0)
            throw std::invalid_argument("max <= 0");
        
        while (max <= value)
            value -= max;
        
        while (value < 0)
            value += max;
        
        return value;
    }
    
    //! Unwrap a range of values
    template <typename Iterator>
    void unwrap(Iterator begin, Iterator end, const typename Iterator::value_type& min, const typename Iterator::value_type& max)
    {
        auto previous = *begin;
        std::advance(begin, 1);
        const auto difference = max - min;
        
        std::transform(begin, end, begin, [&](auto phase)
        {
            while (phase - previous <= min)
                phase += difference;
           
            while (phase - previous > max)
                phase -= difference;
           
            previous = phase;
            return phase.value;
        });
    }
}

#endif /* DSPERADOS_MATH_WRAP_HPP */
