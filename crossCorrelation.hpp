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

#include "convolution.hpp"

namespace math
{
    //! Cross-correlate two buffers, return a buffer with size input + kernel - 1 (output-side algorithm)
    template <typename InputIterator, typename KernelIterator>
    static std::vector<std::common_type_t<typename InputIterator::value_type, typename KernelIterator::value_type>> crossCorrelate(InputIterator inBegin, InputIterator inEnd, KernelIterator kernelBegin, KernelIterator kernelEnd)
    {
        return convolve(inBegin, inEnd, std::make_reverse_iterator(kernelEnd), std::make_reverse_iterator(kernelBegin));
    }
    
    //! Cross-correlate two buffers, return a buffer with size input + kernel - 1 (input-side algorithm)
    template <typename InputIterator, typename KernelIterator>
    static std::vector<std::common_type_t<typename InputIterator::value_type, typename KernelIterator::value_type>> crossCorrelateInputSide(InputIterator inBegin, InputIterator inEnd, KernelIterator kernelBegin, KernelIterator kernelEnd)
    {
        return convolveInputSide(inBegin, inEnd, std::make_reverse_iterator(kernelEnd), std::make_reverse_iterator(kernelBegin));
    }
}

#endif
