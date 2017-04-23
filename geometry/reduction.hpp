//
//  reduction.hpp
//  Math
//
//  Copyright © 2015-2017 Dsperados (info@dsperados.com). All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef MATH_GEOMETRY_REDUCTION_HPP
#define MATH_GEOMETRY_REDUCTION_HPP

#include "rectangular.hpp"
#include "size.hpp"

namespace math
{
    //! Reduce a rectangular
    /*! @relates Rectangular */
    template <class T, std::size_t N, class U>
    auto reduce(const Rectangular<T, N>& rect, const Size<U, N>& reduction)
    {
        return expand(rect, -reduction);
    }

    //! Reduce a rectangle
    /*! @relates Rectangular */
    template <class T, class U, class V>
    auto reduce(const Rectangular<T, 2>& rect, const U& horizontal, const V& vertical)
    {
        return reduce(rect, Size2<std::common_type_t<U, V>>(horizontal, vertical));
    }
}

#endif /* MATH_GEOMETRY_REDUCTION_HPP */
