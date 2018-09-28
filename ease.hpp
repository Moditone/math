//
//  ease.hpp
//  Math
//
//  Copyright © 2015-2018 Moditone (info@moditone.com). All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef MATH_EASE_HPP
#define MATH_EASE_HPP

#include <cmath>

#include "constants.hpp"
#include "interpolation.hpp"

namespace math
{
    //! Revert an easing function to go backwards
    template <typename Function>
    auto revertEase(Function function){ return [=](const auto x){ return function(1 - x); }; }
    
    //! Invert an easing function to its inverse (in/out)
    template <typename Function>
    auto invertEase(Function function){ return [function = revertEase(function)](const auto x){ return 1 - function(x); }; }
    
    //! Combine two easing functions into one ease in-out
    template <typename Function1, typename Function2>
    auto easeInOut(Function1 func1, Function2 func2)
    {
        return [=](const auto x)
        {
            return (x < 0.5) ? func1(x * 2) * 0.5 : func2((x - 0.5) * 2) * 0.5 + 0.5;
        };
    }
    
    //! Turn a single easing function into one ease in-out
    template <typename Function>
    auto easeInOut(Function function)
    {
        return easeInOut(function, invertEase(function));
    }
    
    // Linear
    static const auto easeLinear = [](const auto x){ return x; };
    
    // Exponential forms
    static const auto easeQuadratic = [](const auto x) { return x * x; };
    static const auto easeCubic = [](const auto x) { return x * x * x; };
    static const auto easeQuartic = [](const auto x) { return x * x * x * x; };
    static const auto easeQuintic = [](const auto x) { return x * x * x * x * x; };
    inline auto easeExponential(double exponent) { return [=](const auto x){ return std::pow(x, exponent); }; }
    
    /* Exponential given a middle value
     * 0.5^x = y. Given y, solve x
     * 0.5^x = 0.5^log0.5(y)
     * x = log0.5(y)
     * x = log10(y) / log10(0.5)
     */
    inline auto easeExponentialForCenter(double middleValue) { double exponent = std::log10(middleValue) / -0.3010299957; return [=](const auto x){ return std::pow(x, exponent); }; }
    
    // 1 - e^-x normalised to satisfy x = 1 -> y = 1
    inline auto easeNaturalExponent(double exponent) { return [=](const auto x){ return (1.0 - std::exp(-x * exponent)) / (1.0 - std::exp(-exponent)); }; }
    
    // Sqrt
    static const auto easeSqrt = [](const auto x) { return std::sqrt(x); };
    
    // Circular
    static const auto easeCircular = [](const auto x) { return 1 - std::sqrt(1 - (x * x)); };
    
    // Sine/cosine
    static const auto easeSine = [](const auto x){ return std::sin(x * HALF_PI<decltype(x)>); };
    
    // Elastic
    inline auto easeElastic(double p)
    {
        return [=](const auto x)
        {
            return std::pow(2, -10 * x) * std::sin((x - p / 4) * TWO_PI<decltype(x)> / p) + 1;
        };
    }
    
    // Back
    inline auto easeBack(double s) { return [=](const auto x) { return x * x * ((s + 1) * x - s); }; }
}

#endif /* MATH_EASE_HPP */
