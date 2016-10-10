//
//  constants.hpp
//  Math
//
//  Created by Stijn Frishert (info@stijnfrishert.com) on 16/05/2016.
//  Copyright © 2015-2016 Stijn Frishert. All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef DSPERADOS_MATH_CONSTANTS_HPP
#define DSPERADOS_MATH_CONSTANTS_HPP

namespace math
{
    //! The ubiquitous π
    template <class T> constexpr T PI = 3.1415926535897932384626433832795;
    
    //! 2 * π
    template <class T> constexpr T TWO_PI = PI<T> * 2;
    
    //! Half π
    template <class T> constexpr T HALF_PI = PI<T> * 0.5;
    
    //! A quarter π
    template <class T> constexpr T QUARTER_PI = PI<T> * 0.25;
    
    //! τ, see http://www.tauday.com
    template <class T> constexpr T TAU = TWO_PI<T>;
    
    //! Half τ, see http://www.tauday.com
    template <class T> constexpr T HALF_TAU = PI<T>;
    
    //! Quarter τ, see http://www.tauday.com
    template <class T> constexpr T QUARTER_TAU = HALF_PI<T>;
    
    //! The square root of 2, Pythagoras' constant
    template <class T> constexpr T SQRT_TWO = 1.41421356237309504880168872420969807;
    
    //! Half the square root of 2
    template <class T> constexpr T HALF_SQRT_TWO = SQRT_TWO<T> * 0.5;
    
    //! The square root of 3, Theodorus' constant
    template <class T> constexpr T SQRT_THREE = 1.73205080756887729352744634150587236;
    
    //! The square root of 5
    template <class T> constexpr T SQRT_FIVE = 2.23606797749978969640917366873127623;
    
    //! Euler's number
    template <class T> constexpr T EULER = 2.71828182845904523536028747135266249;
    
    //! The golden ratio
    template <class T> constexpr T PHI = 1.61803398874989484820458683436563811;
}

#endif
