//
//  random.hpp
//  Math
//
//  Copyright © 2015-2017 Dsperados (info@dsperados.com). All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef MATH_LINEAR_RANDOM_HPP
#define MATH_LINEAR_RANDOM_HPP

#include <random>

#include "normalize.hpp"
#include "vector.hpp"

namespace math
{
    template <typename T, std::size_t N, typename Generator>
    Vector<T, N> randomVector(const T& min, const T& max, Generator& generator)
    {
        std::uniform_real_distribution<T> distribution(min, max);

        Vector<T, N> result;
        for (auto i = 0; i < N; ++i)
            result[i] = distribution(generator);

        return result;
    }

    template <typename T, std::size_t N, typename Generator>
    Vector<T, N> randomUnitVector(Generator& generator)
    {
        return normalize(randomVector<T, N, Generator>(-1, 1, generator));
    }
}

#endif /* MATH_LINEAR_LENGTH_HPP */
