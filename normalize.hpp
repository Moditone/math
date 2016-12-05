//
//  Normalize.hpp
//  grizzly
//
//  Created by Milan van der Meer on 16/11/16.
//  Copyright © 2015-2016 Stijn Frishert. All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef MATH_NORMALIZE_HPP
#define MATH_NORMALIZE_HPP

#include <algorithm>
#include <numeric>
#include <stdexcept>

#include "analysis.hpp"

namespace math
{
    //! Normalize an area so the integral of the signal equals one
    template <class InputIterator, class OutputIterator>
    void normalizeArea(InputIterator inBegin, InputIterator inEnd, OutputIterator outBegin)
    {
        auto integral = std::accumulate(inBegin, inEnd, typename InputIterator::value_type{0});
        
        if (!integral)
            throw std::runtime_error("area equals zero");
            
        std::transform(inBegin, inEnd, outBegin, [&](const auto& x){ return x / integral; });
    }
    
    //! Normalize a range
    template <class InputIterator, class OutputIterator>
    void normalize(InputIterator inBegin, InputIterator inEnd, OutputIterator outBegin)
    {
        auto absoluteExtrema = std::abs(*findExtrema(inBegin, inEnd));
        auto factor = 1.l / absoluteExtrema;
        std::transform(inBegin, inEnd, outBegin, [&](const auto& x){ return x * factor; });
    }
}

#endif
