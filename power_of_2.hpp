//
//  utility.hpp
//  Math
//
//  Copyright © 2015-2018 Moditone (info@moditone.com). All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef MODITONE_MATH_UTILITY_HPP
#define MODITONE_MATH_UTILITY_HPP

#include <cstddef>

namespace math
{
    //! Returns whether an integral is a power of two
    /*! @return false for x == 0 */
    constexpr bool isPowerOf2(std::size_t x)
    {
        return (x == 0) ? false : (x == 1 || (x & (x - 1)) == 0);
    }
    
    //! Returns whether an integral is a power of two + 1, useful for checking a spectrum size
    /*! @return false for x == 0 */
    constexpr bool isPowerOf2plus1(std::size_t x)
    {
        return (x == 0) ? false : isPowerOf2(x - 1);
    }
    
    //! Find the smallest power of 2 bigger than a given number
    /*! @return 1 for x == 0 */
    constexpr std::size_t ceilToPowerOf2(std::size_t x)
    {
        std::size_t y = 1;
        while (y < x)
            y <<= 1;
        
        return y;
    }
}

#endif
