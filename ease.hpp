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
    static const auto easeQuadraticIn = [](const auto x) { return x * x; };
    static const auto easeQuadraticOut = invertEase(easeQuadraticIn);
    static const auto easeQuadraticInOut = easeInOut(easeQuadraticIn);
    static const auto easeQuadraticOutIn = easeInOut(easeQuadraticOut);
    
    static const auto easeCubicIn = [](const auto x) { return x * x * x; };
    static const auto easeCubicOut = invertEase(easeCubicIn);
    static const auto easeCubicInOut = easeInOut(easeCubicIn);
    static const auto easeCubicOutIn = easeInOut(easeCubicOut);
    
    static const auto easeQuarticIn = [](const auto x) { return x * x * x * x; };
    static const auto easeQuarticOut = invertEase(easeQuarticIn);
    static const auto easeQuarticInOut = easeInOut(easeQuarticIn);
    static const auto easeQuarticOutIn = easeInOut(easeQuarticOut);
    
    static const auto easeQuinticIn = [](const auto x) { return x * x * x * x * x; };
    static const auto easeQuinticOut = invertEase(easeQuinticIn);
    static const auto easeQuinticInOut = easeInOut(easeQuinticIn);
    static const auto easeQuinticOutIn = easeInOut(easeQuinticOut);

    inline auto easeExponentialIn(double exponent) { return [=](const auto x){ return std::pow(x, exponent); }; }
    inline auto easeExponentialOut(double exponent) { return invertEase(easeExponentialIn(exponent)); }
    inline auto easeExponentialInOut(double exponent) { return easeInOut(easeExponentialIn(exponent)); }
    inline auto easeExponentialOutIn(double exponent) { return easeInOut(easeExponentialOut(exponent)); }
    
    /* Exponential given a middle value
     * 0.5^x = y. Given y, solve x
     * 0.5^x = 0.5^log0.5(y)
     * x = log0.5(y)
     * x = log10(y) / log10(0.5)
     */
    inline auto easeExponentialForCenterIn(double middleValue) { double exponent = std::log10(middleValue) / -0.3010299957; return [=](const auto x){ return std::pow(x, exponent); }; }
    inline auto easeExponentialForCenterOut(double middleValue) { return invertEase(easeExponentialForCenterIn(middleValue)); }
    inline auto easeExponentialForCenterInOut(double middleValue) { return easeInOut(easeExponentialForCenterIn(middleValue)); }
    inline auto easeExponentialForCenterOutIn(double middleValue) { return easeInOut(easeExponentialForCenterOut(middleValue)); }
    
    // 1 - e^-x normalised to satisfy x = 1 -> y = 1
    inline auto easeNaturalExponentIn(double exponent) { return [=](const auto x){ return (1.0 - std::exp(-x * exponent)) / (1.0 - std::exp(-exponent)); }; }
    inline auto easeNaturalExponentOut(double exponent) { return invertEase(easeNaturalExponentIn(exponent)); }
    inline auto easeNaturalExponentInOut(double exponent) { return easeInOut(easeNaturalExponentIn(exponent)); }
    inline auto easeNaturalExponentOutIn(double exponent) { return easeInOut(easeNaturalExponentOut(exponent)); }
    
    // Sqrt
    static const auto easeSqrtIn = [](const auto x) { return std::sqrt(x); };
    static const auto easeSqrtOut = invertEase(easeSqrtIn);
    static const auto easeSqrtInOut = easeInOut(easeSqrtIn);
    static const auto easeSqrtOutIn = easeInOut(easeSqrtOut);
    
    // Circular
    static const auto easeCircularIn = [](const auto x) { return 1 - std::sqrt(1 - (x * x)); };
    static const auto easeCircularOut = invertEase(easeCircularIn);
    static const auto easeCircularInOut = easeInOut(easeCircularIn);
    static const auto easeCircularOutIn = easeInOut(easeCircularOut);
    
    // Sine/cosine
    static const auto easeSineOut = [](const auto x){ return std::sin(x * HALF_PI<decltype(x)>); };
    static const auto easeSineIn = invertEase(easeSineOut);
    static const auto easeSineInOut = easeInOut(easeSineIn);
    static const auto easeSineOutIn = easeInOut(easeSineOut);
    
    // Elastic
    inline auto easeElasticOut(double p)
    {
        return [=](const auto x)
        {
            return std::pow(2, -10 * x) * std::sin((x - p / 4) * TWO_PI<decltype(x)> / p) + 1;
        };
    }
    
    inline auto easeElasticIn(double p) { return invertEase(easeElasticOut(p)); }
    inline auto easeElasticInOut(double p) { return easeInOut(easeElasticIn(p)); }
    inline auto easeElasticOutIn(double p) { return easeInOut(easeElasticOut(p)); }
    
    // Back
    inline auto easeBackIn(double s) { return [=](const auto x) { return x * x * ((s + 1) * x - s); }; }
    inline auto easeBackOut(double p) { return invertEase(easeBackIn(p)); }
    inline auto easeBackInOut(double p) { return easeInOut(easeBackIn(p)); }
    inline auto easeBackOutIn(double p) { return easeInOut(easeBackOut(p)); }
}

#endif /* MATH_EASE_HPP */
