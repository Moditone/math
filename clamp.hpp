//
//  clamp.hpp
//  Math
//
//  Created by Stijn on 07/08/2017.
//
//

#ifndef DSPERADOS_MATH_CLAMP_HPP
#define DSPERADOS_MATH_CLAMP_HPP

#include <stdexcept>
#include <type_traits>

namespace math
{
    //! Clamp a number above a given value
    template <typename T>
    constexpr T clampAbove(const T& value, const T& threshold)
    {
        return value >= threshold ? value : threshold;
    }
    
    //! Clamp a number below a given value
    template <typename T>
    constexpr T clampBelow(const T& value, const T& threshold)
    {
        return value <= threshold ? value : threshold;
    }
    
    //! Clamp a number within a given range
    /*! @throw std::invalid_argument if max < min */
    template <typename T>
    constexpr std::enable_if_t<!std::is_integral<T>::value || std::is_signed<T>::value, T> clamp(const T& value, const T& min, const T& max)
    {
        if (max < min)
            throw std::invalid_argument("max < min");
        
        return clampBelow<T>(clampAbove<T>(value, min), max);
    }
    
    //! Clamp a number within a given range
    /*! @throw std::invalid_argument if max < min */
    template <typename T>
    constexpr std::enable_if_t<std::is_unsigned<T>::value, T> clamp(T value, const T& min, const T& max)
    {
        using T2 = typename std::make_signed<T>::type;
        const auto result = clamp<T2>(static_cast<T2>(value), static_cast<T2>(min), static_cast<T2>(max));
        return static_cast<T>(result);
    }
}

#endif /* DSPERADOS_MATH_CLAMP_HPP */
