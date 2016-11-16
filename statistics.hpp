//
//  statistics.hpp
//  Math
//
//  Created by Stijn Frishert (info@stijnfrishert.com) on 15/11/2016.
//  Copyright © 2015-2016 Stijn Frishert. All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef DSPERADOS_MATH_STATISTICS_HPP
#define DSPERADOS_MATH_STATISTICS_HPP

#include <cmath>
#include <cstddef>
#include <numeric>
#include <vector>


namespace math
{
    //! Calculate the mean
    template <class T, class Iterator>
    inline static T mean(Iterator begin, Iterator end)
    {
        return std::accumulate(begin, end, T(0)) / static_cast<T>(std::distance(begin, end));
    }
    
    //! Calculate the mean square
    template <class T, class Iterator>
    inline static T meanSquare(Iterator begin, Iterator end)
    {
        return std::accumulate(begin, end, T(0), [](const T& accumulatedValue, const T& currentValue) { return accumulatedValue + currentValue * currentValue; }) / static_cast<float>(std::distance(begin, end));
    }
    
    //! Calculate the root mean square
    template <class T, class Iterator>
    inline static T rootMeanSquare(Iterator begin, Iterator end)
    {
        return sqrt(meanSquare<T>(begin, end));
    }
}

#endif
