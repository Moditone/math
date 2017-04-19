//
//  normalize.hpp
//  Math
//
//  Copyright © 2015-2017 Dsperados (info@dsperados.com). All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef MATH_LINEAR_NORMALIZE_HPP
#define MATH_LINEAR_NORMALIZE_HPP

#include <stdexcept>

#include "length.hpp"

namespace math
{
    template <typename T, std::size_t N>
    auto normalize(const Vector<T, N>& vector)
    {
        const auto l = length(vector);
        return (l > 0) ? (vector / l) : Vector<T, N>();
    }
}

#endif /* MATH_LINEAR_NORMALIZE_HPP */
