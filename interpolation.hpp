//
//  interpolation.hpp
//  Math
//
//  Copyright © 2015-2018 Moditone (info@moditone.com). All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef MODITONE_MATH_INTERPOLATION_HPP
#define MODITONE_MATH_INTERPOLATION_HPP

#include <cmath>
#include <cstddef>
#include <functional>
#include <stdexcept>
#include <type_traits>
#include <utility>

#include "access.hpp"
#include "constants.hpp"

namespace math
{
    //! Functor for storing interpolations
    template <typename Iterator>
    using InterpolationFunction = std::function<std::decay_t<decltype(*std::declval<Iterator>())>(Iterator, Iterator, double, AccessorFunction<Iterator>)>;

// --- Interpolation free functions --- //

    //! Choose the nearest of two numbers
    template <typename T, typename Index>
    constexpr auto interpolateNearest(Index index, const T& x1, const T& x2)
    {
        return index < 0.5 ? x1 : x2;
    }
    
    //! Linearly interpolate between numbers
    template <typename T, typename Index>
    constexpr auto interpolateLinear(Index index, const T& x1, const T& x2)
    {
        return x1 + index * (x2 - x1);
    }
    
    //! Interpolate between two numbers using cosine interpolation
    template <typename T, typename Index>
    constexpr auto interpolateCosine(Index index, const T& x1, const T& x2)
    {
        auto t = (1 - cos(index * PI<double>)) / 2.0;
        return x1 + t * (x2 - x1);
    }
    
    //! Interpolate between two numbers using cubic interpolation
    template <typename T, typename Index>
    constexpr auto interpolateCubic(Index index, const T& x1, const T& x2, const T& x3, const T& x4)
    {
        const auto t = index * index;
        const auto a0 = x4 - x3 - x1 + x2;
        const auto a1 = x1 - x2 - a0;
        const auto a2 = x3 - x1;
        const auto a3 = x2;
        
        return(a0 * index * t + a1 * t + a2 * index + a3);
    }
    
    //! Interpolate between two numbers using Catmull-Rom interpolation
    template <typename T, typename Index>
    constexpr auto interpolateCatmullRom(Index index, const T& x1, const T& x2, const T& x3, const T& x4)
    {
        const auto t = index * index;
        const auto a0 = -0.5 * x1 + 1.5 * x2 - 1.5 * x3 + 0.5 * x4;
        const auto a1 = x1 - 2.5 * x2 + 2 * x3 - 0.5 * x4;
        const auto a2 = -0.5 * x1 + 0.5 * x3;
        const auto a3 = x2;
        
        return(a0 * index * t + a1 * t + a2 * index + a3);
    }
    
    //! Interpolate between two numbers using hermite interpolation
    template <typename T, typename Index>
    auto interpolateHermite(Index index, const T& x1, const T& x2, const T& x3, const T& x4, double tension = 0, double bias = 0)
    {
        auto tension2 = (1 - tension) / 2.0;
        
        auto m0  = ((x2 - x1) * (1 + bias) + (x3 - x2) * (1 - bias)) * tension2;
        auto m1  = ((x3 - x2) * (1 + bias) + (x4 - x3) * (1 - bias)) * tension2;
        
        auto t1 = index * index;
        auto t2 = t1 * index;
        
        auto a0 =  2 * t2 - 3 * t1 + 1;
        auto a1 =      t2 - 2 * t1 + index;
        auto a2 =      t2 -     t1;
        auto a3 = -2 * t2 + 3 * t1;
        
        return (a0 * x2 + a1 * m0 + a2 * m1 + a3 * x3);
    }
    
    //! Interpolate a parabolic peak between three equidistant values
    template <typename T>
    constexpr std::pair<double, T> interpolateParabolic(const T& x1, const T& x2, const T& x3)
    {
        const auto d = x1 - x3;
        auto offset = 0.5 * d / (x1 - 2 * x2 + x3);
        auto peak = x2 - 0.25 * d * offset;
        
        return {offset, peak};
    }

// --- Interpolation lambda's --- //
    
    //! Lambda executing nearest interpolation
    template <typename Iterator, typename Accessor>
    auto interpolateNearest(Iterator begin, Iterator end, std::ptrdiff_t index, Accessor access) -> typename std::iterator_traits<Iterator>::value_type
    {
        const auto trunc = static_cast<std::ptrdiff_t>(std::floor(index));
        const auto fraction = index - trunc;
        
        const auto x1 = access(begin, end, trunc);
        const auto x2 = access(begin, end, trunc + 1);
        
        return interpolateNearest(fraction, x1, x2);
    };
    
    //! Lambda executing linear interpolation
    template <typename Iterator, typename Accessor>
    auto interpolateLinear(Iterator begin, Iterator end, std::ptrdiff_t index, Accessor access) -> typename std::iterator_traits<Iterator>::value_type
    {
        const auto trunc = static_cast<std::ptrdiff_t>(std::floor(index));
        const auto fraction = index - trunc;
        
        const auto x1 = access(begin, end, trunc);
        const auto x2 = access(begin, end, trunc + 1);
        
        return interpolateLinear(fraction, x1, x2);
    };
    
    //! Lambda executing cosine interpolation
    template <typename Iterator, typename Accessor>
    auto interpolateCosine(Iterator begin, Iterator end, std::ptrdiff_t index, Accessor access) -> typename std::iterator_traits<Iterator>::value_type
    {
        const auto trunc = static_cast<std::ptrdiff_t>(std::floor(index));
        const auto fraction = index - trunc;
        
        const auto x1 = access(begin, end, trunc);
        const auto x2 = access(begin, end, trunc + 1);
        
        return interpolateCosine(fraction, x1, x2);
    };
    
    //! Lambda executing cosine interpolation
    template <typename Iterator, typename Accessor>
    auto interpolateCubic(Iterator begin, Iterator end, std::ptrdiff_t index, Accessor access) -> typename std::iterator_traits<Iterator>::value_type
    {
        const auto trunc = static_cast<std::ptrdiff_t>(std::floor(index));
        const auto fraction = index - trunc;
        
        const auto x1 = access(begin, end, trunc - 1);
        const auto x2 = access(begin, end, trunc);
        const auto x3 = access(begin, end, trunc + 1);
        const auto x4 = access(begin, end, trunc + 2);
        
        return interpolateCubic(fraction, x1, x2, x3, x4);
    };
    
    //! Lambda executing cosine interpolation
    template <typename Iterator, typename Accessor>
    auto interpolateCatmullRom(Iterator begin, Iterator end, std::ptrdiff_t index, Accessor access) -> typename std::iterator_traits<Iterator>::value_type
    {
        const auto trunc = static_cast<std::ptrdiff_t>(std::floor(index));
        const auto fraction = index - trunc;
        
        const auto x1 = access(begin, end, trunc - 1);
        const auto x2 = access(begin, end, trunc);
        const auto x3 = access(begin, end, trunc + 1);
        const auto x4 = access(begin, end, trunc + 2);
        
        return interpolateCatmullRom(fraction, x1, x2, x3, x4);
    };
    
    //! Generate a lambda executing hermite interpolation
    template <typename Iterator, typename Accessor>
    auto interpolateHermite(Iterator begin, Iterator end, std::ptrdiff_t index, Accessor access, double tension = 0, double bias = 0)
        -> typename std::iterator_traits<Iterator>::value_type
    {
        const auto trunc = static_cast<std::ptrdiff_t>(std::floor(index));
        const auto fraction = index - trunc;
        
        const auto x1 = access(begin, end, trunc - 1);
        const auto x2 = access(begin, end, trunc);
        const auto x3 = access(begin, end, trunc + 1);
        const auto x4 = access(begin, end, trunc + 2);
        
        return interpolateHermite(fraction, x1, x2, x3, x4, tension, bias);
    }

// --- Other functions using interpolation --- //
    
    //! Scale a number from one range to another
    /*! @throw std::invalid_argument if max1 <= min1 */
    template <typename T1, typename T2, typename T3, typename T4, typename T5>
    auto scale(const T1& value, const T2& begin1, const T3& end1, const T4& begin2, const T5& end2)
    {
        return interpolateLinear((value - begin1) / static_cast<long double>(end1 - begin1), begin2, end2);
    }
    
    //! Scale a number from one range to another with a skew factor computed from a middle value
    /*! @throw std::invalid_argument if max1 <= min1 and if middle2 <= min2 or middle2 >= max2 */
    template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    auto skew(const T1& value, const T2& begin1, const T3& end1, const T4& begin2, const T5& middle2, const T6& end2)
    {
        // Solve exponent for 0.5^exponent * (max2 - min2) = middle2
        auto temp = (middle2 - begin2) / static_cast<long double>(end2 - begin2);
        auto exponent = log10l(temp) / log10l(0.5l);
        
        auto normalisedValue = scale(value, begin1, end1, 0.0l, 1.0l);
        
        return powl(normalisedValue, exponent) * (end2 - begin2) + begin2;
    }
    
    //! Convert from a linear to a logarithmic scale
    /*! @throw std::invalid_argument if min2 or max2 <= 0 */
    template <typename T1, typename T2, typename T3, typename T4, typename T5>
    auto lin2log(const T1& value, const T2& min1, const T3& max1, const T4& min2, const T5& max2)
    {
        if (min2 <= 0)
            throw std::invalid_argument("min2 <= 0");
        
        if (max2 <= 0)
            throw std::invalid_argument("max2 <= 0");
        
        const auto exponent = scale(value, min1, max1, log(min2), log(max2));
        return exp(exponent);
    }
    
    //! Convert from a logarithmic to a linear scale
    /*! @throw std::invalid_argument if value, min1 or max1 <= 0 */
    template <typename T1, typename T2, typename T3, typename T4, typename T5>
    auto log2lin(const T1& value, const T2& min1, const T3& max1, const T4& min2, const T5& max2)
    {
        if (value <= 0)
            throw std::invalid_argument("value <= 0");
        
        if (min1 <= 0)
            throw std::invalid_argument("min1 <= 0");
        
        if (max1 <= 0)
            throw std::invalid_argument("max1 <= 0");
        
        return scale<double>(log(value), log(min1), log(max1), min2, max2);
    }
}

#endif
