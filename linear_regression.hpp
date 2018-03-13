//
//  linear_regression.hpp
//  Math
//
//  Copyright © 2015-2018 Moditone (info@moditone.com). All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef MODITONE_MATH_LINEAR_REGRESSION_HPP
#define MODITONE_MATH_LINEAR_REGRESSION_HPP

#include <cstddef>
#include <iterator>
#include <numeric>
#include <vector>

namespace math
{
    //! Linear Coefficients
    /*  Linear Coefficients express the form y = a + bx and contain the parameters a (offset) and b (slope) */
    template <class T>
    struct LinearCoefficients
    {
        LinearCoefficients(const T& offset, const T& slope) : offset(offset), slope(slope) { }
        
        // Y-intercept
        T offset = 0;
        
        //! Slope
        T slope = 0;
    };
    
    //! Find the coefficients for a linear curve that best fit the data
    template <class Iterator>
    LinearCoefficients<typename Iterator::value_type> regressLinear(Iterator beginX, Iterator endX, Iterator beginY, Iterator endY)
    {
        const auto zero = typename Iterator::value_type(0);
        
        // Number of data points
        const auto N = std::distance(beginX, endX);
        
        // Sum of x
        const auto sumX = std::accumulate(beginX, endX, zero);
        
        // Sum of y
        const auto sumY = std::accumulate(beginY, endY, zero);
        
        // Sum of x * y
        std::size_t i = 0;
        const auto sumXY = std::accumulate(beginX, endX, zero, [&](const auto& sum, const auto& value){ return sum + (value * *(beginY + i++)); });
        
        // Sum of x^2
        const auto sumX2 = std::accumulate(beginX, endX, zero, [](const auto& sum, const auto& value){ return sum + (value * value); });
        
        // Compute the a (y-intercept) and b (slope) coefficients
        auto offset = static_cast<typename Iterator::value_type>(((sumY * sumX2) - (sumX * sumXY)) / ((N * sumX2) - (sumX * sumX)));
        auto slope = static_cast<typename Iterator::value_type>(((N * sumXY) - (sumX * sumY)) / ((N * sumX2) - (sumX * sumX)));
        
        return {offset, slope};
    }
    
    //! Find the coefficients for a linear curve that best fit the data
    template <class Iterator>
    LinearCoefficients<typename Iterator::value_type> regressLinear(Iterator beginY, Iterator endY)
    {
        // Create an ascending vector from 0 for the x-points
        std::vector<float> x(std::distance(beginY, endY));
        std::iota(x.begin(), x.end(), typename Iterator::value_type(0));
        
        // Compute regression
        return regressLinear(x.begin(), x.end(), beginY, endY);
    }
}

#endif /* MODITONE_MATH_LINEAR_REGRESSION_HPP */
