//
//  crossCorrelation.hpp
//  Math
//
//  Copyright © 2015-2017 Dsperados (info@dsperados.com). All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef DSPERADOS_MATH_CROSSCORRELATION_HPP
#define DSPERADOS_MATH_CROSSCORRELATION_HPP

#include <iterator>

namespace math
{
    //! Cross-correlate two buffers, return a buffer with size input + kernel - 1 (output-side algorithm)
    template <typename InputIterator, typename KernelIterator>
    static std::vector<std::common_type_t<typename InputIterator::value_type, typename KernelIterator::value_type>> crossCorrelate(InputIterator inBegin, InputIterator inEnd, KernelIterator kernelBegin, KernelIterator kernelEnd)
    {
        auto inputSize = std::distance(inBegin, inEnd);
        auto kernelSize = std::distance(kernelBegin, kernelEnd);
        auto size = inputSize + kernelSize - 1;
        
        vector<float> output(size);
        for (auto i = 0 ; i < size; i++)
            for (auto h = 0; h < kernelSize; h++)
            {
                if (i - h < 0) continue;
                else if (i - h >= inputSize) continue;
                output[i] += kernelBegin[kernelSize - 1 - h] * inBegin[i - h];
            }
        
        return output;
    }
    
    //! Cross-correlate two buffers, return a buffer with size input + kernel - 1 (input-side algorithm)
    template <typename InputIterator, typename KernelIterator>
    static std::vector<std::common_type_t<typename InputIterator::value_type, typename KernelIterator::value_type>> crossCorrelateInputSide(InputIterator inBegin, InputIterator inEnd, KernelIterator kernelBegin, KernelIterator kernelEnd)
    {
        auto inputSize = std::distance(inBegin, inEnd);
        auto kernelSize = std::distance(kernelBegin, kernelEnd);
        auto size = inputSize + kernelSize - 1;
        
        vector<float> output(size);
        for (auto i = 0; i < inputSize; i++)
            for (auto h = 0; h < kernelSize; h++)
                output[i+h] += kernelBegin[kernelSize - 1 - h] * inBegin[i];
        
        return output;
    }
}

#endif
