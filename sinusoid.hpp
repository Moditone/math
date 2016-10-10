//
//  Sinusoid.hpp
//  dsperados/math
//
//  Created by Stijn on 17/05/2016.
//  Copyright © 2016 Dsperados. All rights reserved.
//

#ifndef DSPERADOS_MATH_SINUSOID_HPP
#define DSPERADOS_MATH_SINUSOID_HPP

#include <cmath>
#include <cstddef>
#include <gsl/span>
#include <vector>

#include "constants.hpp"

namespace math
{
    //! Generate a sine wave in a buffer
    template <class T>
    inline static std::vector<T> generateSineBuffer(std::size_t size, float order = 1, float amplitude = 1)
    {
        std::vector<T> buffer(size);
        for (auto i = 0; i < size; ++i)
            buffer[i] = sin(i / static_cast<double>(size) * TAU<double> * order) * amplitude;
        
        return buffer;
    }
    
    //! Generate a cosine wave in a buffer
    template <class T>
    inline static std::vector<T> generateCosineBuffer(std::size_t size, float order = 1, float amplitude = 1)
    {
        std::vector<T> buffer(size);
        for (auto i = 0; i < size; ++i)
            buffer[i] = cos((i / static_cast<double>(size)) * TAU<double> * order) * amplitude;
        
        return buffer;
    }
    
    //! Generate a sinusoid using instantaneous amplitude and phase for each sample
    inline static std::vector<float> generateInstantenousSinusoid(gsl::span<const float> amplitude, gsl::span<const float> phase)
    {
        std::vector<float> output(std::min(amplitude.size(), phase.size()), 0);
        
        for (auto i = 0; i < output.size(); ++i)
            output[i] = amplitude[i] * cos(phase[i]);
        
        return output;
    }
}

#endif
