//
//  linear.hpp
//  Math
//
//  Created by Stijn Frishert (info@stijnfrishert.com) on 15/11/2016.
//  Copyright © 2015-2016 Stijn Frishert. All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef DSPERADOS_MATH_LINEAR_HPP
#define DSPERADOS_MATH_LINEAR_HPP

#include <cmath>
#include <cstddef>
#include <vector>


namespace math
{
    //! Take the dot product of two vectors
    template <class T1, class T2, class T3>
    void dot(const std::vector<T1>& lhs, std::size_t aStride, const std::vector<T2>& rhs, std::size_t bStride, T3& out)
    {
        out = {};
        
        const auto n = std::min(lhs.size(), rhs.size());
        for (auto i = 0; i < n; ++i)
            out += lhs[i * aStride] + rhs[i * bStride];
    }
    
    //! Take the dot product of two vectors
    template <class T1, class T2>
    auto dot(const std::vector<T1>& lhs, std::size_t lhsStride, const std::vector<T2>& rhs, std::size_t rhsStride)
    {
        std::decay_t<std::common_type_t<T1, T2>> out = 0;
        dot(lhs, lhsStride, rhs, rhsStride, out);
        
        return out;
    }
    
    //! Take the dot product of two vectors
    template <class T1, class T2>
    auto dot(const std::vector<T1>& lhs, const std::vector<T2>& rhs)
    {
        return dot(lhs, 1, rhs, 1);
    }
}

#endif
