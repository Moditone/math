//
//  exp.hpp
//  Math
//
//  Copyright © 2015-2017 Dsperados (info@dsperados.com). All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef MATH_LINEAR_EXP_HPP
#define MATH_LINEAR_EXP_HPP

#include <algorithm>
#include <cmath>
#include <type_traits>

#include "vector.hpp"

namespace math
{
    template <typename T1, typename T2, std::size_t N>
    auto exp(const Vector<T1, N>& lhs, const Vector<T2, N>& rhs)
    {
        using T = std::common_type_t<T1, T2>;
        Vector<T, N> result;
        std::transform(lhs.begin(), lhs.end(), rhs.begin(), result.begin(), [&](auto& a, auto& b){ return std::exp(a, b); });
        return result;
    }
}

namespace std
{
    template <typename T1, typename T2, std::size_t N>
    auto pow(const math::Vector<T1, N>& lhs, const math::Vector<T2, N>& rhs)
    {
        return exp(lhs, rhs);
    }
}

#endif
