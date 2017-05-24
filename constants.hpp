//
//  constants.hpp
//  Math
//
//  Copyright © 2015-2017 Dsperados (info@dsperados.com). All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef DSPERADOS_MATH_CONSTANTS_HPP
#define DSPERADOS_MATH_CONSTANTS_HPP

namespace math
{
    template <class T> const T PI = T(3.1415926535897932384626433832795); //!< The ubiquitous π
    template <class T> const T TWO_PI = PI<T> * 2; //!< 2 * π
    template <class T> const T HALF_PI = PI<T> * 0.5; //!< Half π
    template <class T> const T QUARTER_PI = PI<T> * 0.25; //!< A quarter π
    
    template <class T> const T TAU = TWO_PI<T>; //!< τ, see http://www.tauday.com
    template <class T> const T HALF_TAU = PI<T>; //!< Half τ, see http://www.tauday.com
    template <class T> const T QUARTER_TAU = HALF_PI<T>; //!< Quarter τ, see http://www.tauday.com
    
    template <class T> const T SQRT_TWO = T(1.41421356237309504880168872420969807); //!< The square root of 2, Pythagoras' constant
    template <class T> const T HALF_SQRT_TWO = SQRT_TWO<T> * 0.5; //!< Half the square root of 2
    template <class T> const T SQRT_HALF = HALF_SQRT_TWO<T>; //! < The square root of 0.5
    template <class T> const T SQRT_THREE = T(1.73205080756887729352744634150587236); //!< The square root of 3, Theodorus' constant
    template <class T> const T SQRT_FIVE = T(2.23606797749978969640917366873127623); //!< The square root of 5
    
    template <class T> const T EULER = T(2.71828182845904523536028747135266249); //!< Euler's number
    
    template <class T> const T PHI = T(1.61803398874989484820458683436563811); //!< The golden ratio
    template <class T> const T INVERSE_PHI = T{1} / PHI<T>; //!< The golden ratio
    template <class T> const T GOLDEN_RATIO = INVERSE_PHI<T>;
}

#endif
