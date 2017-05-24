//
//  interleave.hpp
//  Math
//
//  Copyright © 2015-2017 Dsperados (info@dsperados.com). All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef DSPERADOS_MATH_INTERLEAVE_HPP
#define DSPERADOS_MATH_INTERLEAVE_HPP

#include <cmath>
#include <complex>
#include <cstddef>
#include <iterator>
#include <vector>

namespace math
{
    //! Interleave two ranges
    template <typename InputIt1, typename InputIt2, typename OutputIt>
    void interleave(InputIt1 inBegin1, InputIt1 inEnd, InputIt2 inBegin2, OutputIt outBegin)
    {
        while (inBegin1 != inEnd)
        {
            *outBegin = static_cast<std::decay_t<decltype(*outBegin)>>(*inBegin1);
            std::advance(outBegin, 1);
            std::advance(inBegin1, 1);
            
            *outBegin = static_cast<std::decay_t<decltype(*outBegin)>>(*inBegin2);
            std::advance(outBegin, 1);
            std::advance(inBegin2, 1);
        }
    }
    
    //! Deinterleave a range into two ranges
    template <typename InputIt, typename OutputIt1, typename OutputIt2>
    void deinterleave(InputIt inBegin, InputIt inEnd, OutputIt1 outBegin1, OutputIt2 outBegin2)
    {
        while (inBegin != inEnd)
        {
            *outBegin1 = static_cast<std::decay_t<decltype(*outBegin1)>>(*inBegin);
            std::advance(outBegin1, 1);
            std::advance(inBegin, 1);
            
            *outBegin2 = static_cast<std::decay_t<decltype(*outBegin2)>>(*inBegin);
            std::advance(outBegin2, 1);
            std::advance(inBegin, 1);
        }
    }
}

#endif
