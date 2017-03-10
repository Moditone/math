//
//  interpolation.hpp
//  Math
//
//  Copyright © 2015-2016 Dsperados (info@dsperados.com). All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef DSPERADOS_MATH_INTERPOLATION_HPP
#define DSPERADOS_MATH_INTERPOLATION_HPP

#include <cmath>
#include <functional>
#include <stdexcept>
#include <utility>

#include "access.hpp"
#include "constants.hpp"

namespace math
{
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
    static inline auto interpolateHermite(Index index, const T& x1, const T& x2, const T& x3, const T& x4, double tension = 0, double bias = 0)
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
    
    //! Lambda executing nearest interpolation
    static const auto nearestInterpolation = [](auto begin, auto end, auto index, auto accessor)
    {
        const std::ptrdiff_t trunc = std::floor(index);
        const auto fraction = index - trunc;
        
        const auto x1 = access(begin, end, trunc, accessor);
        const auto x2 = access(begin, end, trunc + 1, accessor);
        
        return interpolateNearest(fraction, x1, x2);
    };
    
    //! Lambda executing linear interpolation
    static const auto linearInterpolation = [](auto begin, auto end, auto index, auto accessor)
    {
        const std::ptrdiff_t trunc = std::floor(index);
        const auto fraction = index - trunc;
        
        const auto x1 = access(begin, end, trunc, accessor);
        const auto x2 = access(begin, end, trunc + 1, accessor);
        
        return interpolateLinear(fraction, x1, x2);
    };
    
    //! Lambda executing cosine interpolation
    static const auto cosineInterpolation = [](auto begin, auto end, auto index, auto accessor)
    {
        const std::ptrdiff_t trunc = std::floor(index);
        const auto fraction = index - trunc;
        
        const auto x1 = access(begin, end, trunc, accessor);
        const auto x2 = access(begin, end, trunc + 1, accessor);
        
        return interpolateCosine(fraction, x1, x2);
    };
    
    //! Lambda executing cosine interpolation
    static const auto cubicInterpolation = [](auto begin, auto end, auto index, auto accessor)
    {
        const std::ptrdiff_t trunc = std::floor(index);
        const auto fraction = index - trunc;
        
        const auto x1 = access(begin, end, trunc - 1, accessor);
        const auto x2 = access(begin, end, trunc, accessor);
        const auto x3 = access(begin, end, trunc + 1, accessor);
        const auto x4 = access(begin, end, trunc + 2, accessor);
        
        return interpolateCubic(fraction, x1, x2, x3, x4);
    };
    
    //! Lambda executing cosine interpolation
    static const auto catmullRomInterpolation = [](auto begin, auto end, auto index, auto accessor)
    {
        const std::ptrdiff_t trunc = std::floor(index);
        const auto fraction = index - trunc;
        
        const auto x1 = access(begin, end, trunc - 1, accessor);
        const auto x2 = access(begin, end, trunc, accessor);
        const auto x3 = access(begin, end, trunc + 1, accessor);
        const auto x4 = access(begin, end, trunc + 2, accessor);
        
        return interpolateCatmullRom(fraction, x1, x2, x3, x4);
    };
    
    //! Generate a lambda executing hermite interpolation
    inline auto hermiteInterpolation(double tension = 0, double bias = 0)
    {
        return [tension, bias](auto begin, auto end, auto index, auto accessor)
        {
            const std::ptrdiff_t trunc = std::floor(index);
            const auto fraction = index - trunc;
            
            const auto x1 = access(begin, end, trunc - 1, accessor);
            const auto x2 = access(begin, end, trunc, accessor);
            const auto x3 = access(begin, end, trunc + 1, accessor);
            const auto x4 = access(begin, end, trunc + 2, accessor);
            
            return interpolateCatmullRom(fraction, x1, x2, x3, x4);
        };
    }
    
    //! Functor for storing interpolations
    template <typename Iterator>
    using InterpolationFunction = std::function<decltype(*std::declval<Iterator>())(Iterator, Iterator, std::ptrdiff_t, AccessorFunction<Iterator>)>;

    //! Access an interpolated sample in a range, taking an interpolator and accessor
    template <typename Iterator, typename Index, class Interpolator, typename Accessor>
    auto interpolate(Iterator begin, Iterator end, Index index, Interpolator interpolator, Accessor accessor)
    {
        return interpolator(begin, end, index, accessor);
    }

    //! Scale a number from one range to another
    /*! @throw std::invalid_argument if max1 <= min1 */
    template <typename T1, typename T2, typename T3, typename T4, typename T5>
    auto scale(const T1& value, const T2& min1, const T3& max1, const T4& min2, const T5& max2)
    {
        if (max1 <= min1)
            throw std::invalid_argument("max1 <= min1");

        return interpolateLinear((value - min1) / static_cast<long double>(max1 - min1), min2, max2);
    }

    //! Scale a number from one range to another with a skew factor computed from a middle value
    /*! @throw std::invalid_argument if max1 <= min1 and if middle2 <= min2 or middle2 >= max2 */
    template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    auto skew(const T1& value, const T2& min1, const T3& max1, const T4& min2, const T5& middle2, const T6& max2)
    {
        if (max1 <= min1)
            throw std::invalid_argument("max1 <= min1");
        if (max2 > min2 && (middle2 <= min2 || middle2 >= max2))
            throw std::invalid_argument("middle2 not in bounds van min2 and max2");
        else if (max2 < min2 && (middle2 >= min2 || middle2 <= max2))
            throw std::invalid_argument("middle2 not in bounds van min2 and max2");

        // Solve exponent for 0.5^exponent * (max2 - min2) = middle2
        auto temp = (middle2 - min2) / static_cast<long double>(max2 - min2);
        auto exponent = log10l(temp) / log10l(0.5l);

        auto normalisedValue = scale(value, min1, max1, 0.0l, 1.0l);

        return powl(normalisedValue, exponent) * (max2 - min2) + min2;
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
