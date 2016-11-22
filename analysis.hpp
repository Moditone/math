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
#include <iterator>
#include <vector>

namespace math
{
    //! Find the absolute peak of a signal
    template <class Iterator>
    Iterator findAbsolutePeak(Iterator begin, Iterator end)
    {
        auto range = std::minmax_element(begin, end);
        const auto min = std::abs(*range.first);
        if (min == *range.second)
            return std::min(range.first, range.second);
        else if (min < *range.second)
            return range.second;
        else
            return range.first;
    }
    
    //! Find the local minima of a signal
    template <class Iterator>
    std::vector<size_t> findLocalMinimaPositions(Iterator begin, Iterator end)
    {
        // If we only received two points or less, there is no minimum
        const auto d = std::distance(begin, end);
        if (d < 3)
            return {};
        
        // Store three iterators for the previous, current and next sample
        auto p = begin;
        auto c = std::next(p);
        auto n = std::next(c);
        
        // Loop through the range, storing the position of each minimum
        std::vector<size_t> minima;
        for (size_t pos = 1; c != end; ++pos)
        {
            // Is the previous sample bigger than the current, and the current smaller or equal than the next?
            if (*p > *c && *c <= *n)
                minima.emplace_back(pos);
            
            // Move the iterators forward
            p = c;
            c = n++;
        }
        
        return minima;
    }
    
    //! Find the local minima of a signal
    template <class Iterator>
    std::vector<size_t> findLocalMaximaPositions(Iterator begin, Iterator end)
    {
        // If we only received two points or less, there is no maximum
        const auto d = std::distance(begin, end);
        if (d < 3)
            return {};
        
        // Store three iterators for the previous, current and next sample
        auto p = begin;
        auto c = std::next(p);
        auto n = std::next(c);
        
        // Loop through the range, storing the position of each maximum
        std::vector<size_t> maxima;
        for (size_t pos = 1; c != end; ++pos)
        {
            // Is the previous sample smaller than the current, and the current bigger or equal than the next?
            if (*p < *c && *c >= *n)
                maxima.emplace_back(pos);
            
            // Move the iterators forward
            p = c;
            c = n++;
        }
        
        return maxima;
    }
    
    //! Count the number of zero crossings in a span
    template <class Iterator>
    size_t countZeroCrossings(Iterator begin, Iterator end)
    {
        // If we only received one points or less, there can be no zero crossings
        const auto d = std::distance(begin, end);
        if (d < 2)
            return 0;
        
        // Store two iterators
        auto p = begin;
        auto n = std::next(p);
        
        size_t count = 0;
        while (n != end)
        {
            if (std::signbit(*p) != std::signbit(*n))
                ++count;
            
            p = n++;
        }
        
        return count;
    }
}

#endif
