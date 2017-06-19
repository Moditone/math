//
//  linear_regression.hpp
//  Math
//
//  Copyright © 2015-2017 Dsperados (info@dsperados.com). All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef DSPERADOS_MATH_LINEAR_REGRESSION_HPP
#define DSPERADOS_MATH_LINEAR_REGRESSION_HPP

#include <iterator>
#include <numeric>
#include <vector>

namespace math
{
    //! Linear Coefficients
    /*  Linear Coefficients express the form y = a + bx and contain the parameters a (y-intercept) and b (slope) */
    template <class T>
    struct LinearCoefficients
    {
        LinearCoefficients(const T& a, const T& b) : a(a), b(b) {}
        
        // Y-intercept
        T a = 0;
        
        //! Slope
        T b = 0;
    };
    
    //! Find the coefficients for a linear curve that best fit the data
    template <class Iterator>
    LinearCoefficients<typename Iterator::value_type> regressLinear(Iterator beginX, Iterator endX, Iterator beginY, Iterator endY)
    {
        // Number of data points
        auto N = std::distance(beginX, endX);
        
        // Sum of x
        auto sumX = std::accumulate(beginX, endX, 0);
        
        // Sum of y
        auto sumY = std::accumulate(beginY, endY, 0);
        
        // Sum of x * y
        size_t i = 0;
        auto sumXY = std::accumulate(beginX, endX, 0, [&](const auto& sum, const auto& value){ return sum + (value * *(beginY + i++)); });
        
        // Sum of x^2
        auto sumX2 = std::accumulate(beginX, endX, 0, [](const auto& sum, const auto& value){ return sum + (value * value); });
        
        // Compute the a (y-intercept) and b (slope) coefficients
        auto a = static_cast<typename Iterator::value_type>(((sumY * sumX2) - (sumX * sumXY)) / ((N * sumX2) - (sumX * sumX)));
        auto b = static_cast<typename Iterator::value_type>(((N * sumXY) - (sumX * sumY)) / ((N * sumX2) - (sumX * sumX)));
        
        return {a, b};
    }
    
    //! Find the coefficients for a linear curve that best fit the data
    template <class Iterator>
    LinearCoefficients<typename Iterator::value_type> regressLinear(Iterator beginY, Iterator endY)
    {
        // Create an ascending vector from 0 for the x-points
        std::vector<float> x(std::distance(beginY, endY));
        std::iota(x.begin(), x.end(), 0);
        
        // Compute regression
        return regressLinear(x.begin(), x.end(), beginY, endY);
    }
}

#endif /* DSPERADOS_MATH_LINEAR_REGRESSION_HPP */
