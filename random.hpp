//
//  Random.hpp
//  dsperados/math
//
//  Created by Stijn on 17/05/2016.
//  Copyright © 2016 Dsperados. All rights reserved.
//

#ifndef DSPERADOS_MATH_RANDOM_HPP
#define DSPERADOS_MATH_RANDOM_HPP

#include <cstddef>
#include <random>
#include <type_traits>
#include <vector>

#include "constants.hpp"

namespace math
{
    //! Generate a random integral uniform sample
    template <class T, class Engine, class Min, class Max>
    inline static std::enable_if_t<std::is_integral<T>::value, T> generateUniformRandom(const Min& a, const Max& b, Engine& engine)
    {
        return std::uniform_int_distribution<T>(a, b)(engine);
    }
    
    //! Generate a random floating-point uniform sample
    template <class T, class Engine, class Min, class Max>
    inline static std::enable_if_t<std::is_floating_point<T>::value, T> generateUniformRandom(const Min& a, const Max& b, Engine& engine)
    {
        return std::uniform_real_distribution<T>(a, b)(engine);
    }
    
    //! Generate a random uniform buffer
    template <class T, class Engine, class Min, class Max>
    inline static std::vector<T> generateUniformRandomBuffer(std::size_t size, const Min& a, const Max& b, Engine& engine)
    {
        std::vector<T> result(size);
        std::generate(result.begin(), result.end(), [&]{ return generateUniformRandom<T>(a, b, engine); });
        
        return result;
    }
}

#endif
