//
//  ease.hpp
//  math
//
//  Created by Stijn Frishert on 15/11/16.
//
//

#ifndef MATH_EASE_HPP
#define MATH_EASE_HPP

#include <cmath>

#include "interpolation.hpp"

namespace math
{
    //! Ease using linear interpolation
    template <class T>
    constexpr T easeLinear(const T& index)
    {
        return interpolateLinear<T>(index, 0, 1);
    }
    
    //! Ease using cosine interpolation
    template <class T>
    constexpr T easeCosine(const T& index)
    {
        return interpolateCosine<T>(index, 0, 1);
    }
    
    //! Ease using
    template <class T>
    constexpr T easeCircular(const T& index)
    {
        return 1 - std::sqrt(1 - (index * index));
    }
}

#endif /* MATH_EASE_HPP */
