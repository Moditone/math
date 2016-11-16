//
//  analysis.hpp
//  Math
//
//  Created by Stijn Frishert (info@stijnfrishert.com) on 15/11/2016.
//  Copyright © 2015-2016 Stijn Frishert. All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef DSPERADOS_MATH_ANALYSIS_HPP
#define DSPERADOS_MATH_ANALYSIS_HPP

#include <cmath>
#include <cstddef>
#include <vector>

namespace math
{
    //! Find the local minima of a signal
    template <class T>
    inline static auto localMinima(const std::vector<T>& input)
    {
        std::vector<size_t> minima;
        for (auto i = 1; i < input.size() - 1; ++i)
        {
            if (input[i - 1] > input[i] && input[i] <= input[i + 1])
                minima.emplace_back(i);
        }
        
        return minima;
    }
    
    //! Find the local maxima of a signal
    template <class T>
    inline static auto localMaxima(const std::vector<T>& input)
    {
        std::vector<size_t> maxima;
        for (auto i = 1; i < input.size() - 1; ++i)
        {
            if (input[i - 1] < input[i] && input[i] >= input[i + 1])
                maxima.emplace_back(i);
        }
        
        return maxima;
    }
    
    //! Count the number of zero crossings in a span
    template <class T>
    inline static size_t zeroCrossings(const std::vector<T>& input)
    {
        size_t count = 0;
        for (auto i = 1; i < input.size(); ++i)
        {
            if (std::signbit(input[i]) != std::signbit(input[i-1]))
                ++count;
        }
        
        return count;
    }
}

#endif
