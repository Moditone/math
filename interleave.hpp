//
//  interleave.hpp
//  Math
//
//  Created by Stijn Frishert (info@stijnfrishert.com) on 15/11/2016.
//  Copyright © 2015-2016 Stijn Frishert. All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef DSPERADOS_MATH_INTERLEAVE_HPP
#define DSPERADOS_MATH_INTERLEAVE_HPP

#include <cmath>
#include <complex>
#include <cstddef>
#include <vector>


namespace math
{
    template <class InputIterator, class OutputIterator>
    void interleave(InputIterator inBegin1)
    
    //! Interleave two vectors
    template <class T1, class T2, class T3>
    void interleave(const std::vector<T1>& lhs, const std::vector<T2>& rhs, std::vector<T3>& out)
    {
        const auto n = std::min({lhs.size(), rhs.size(), out.size() / 2});
        
        for (auto i = 0; i < n; ++i)
        {
            out[i * 2] = lhs[i];
            out[i * 2 + 1] = rhs[i];
        }
    }
    
    template <class T1, class T2, class T3>
    void interleave(const std::vector<T1>& lhs, const std::vector<T2>& rhs, std::vector<std::complex<T3>>& out)
    {
        std::vector<T3> fout(out.size() * 2);
        interleave(lhs, rhs, fout);
        
        for (auto i = 0; i < out.size(); ++i)
        {
            out[i].real(fout[i * 2]);
            out[i].imag(fout[i * 2 + 1]);
        }
    }
    
    //! Interleave two spans
    template <class T1, class T2>
    auto interleave(const std::vector<T1>& lhs, const std::vector<T2>& rhs)
    {
        using T3 = std::decay_t<std::common_type_t<T1, T2>>;
        std::vector<T3> out(std::min(lhs.size(), rhs.size()) * 2);
        interleave(lhs, rhs, out);
        return out;
    }
    
    //! Deinterleave a span
    template <class T1, class T2, class T3>
    void deinterleave(const std::vector<T1>& in, std::vector<T2>& lhs, std::vector<T3>& rhs)
    {
        const auto n = std::min({in.size() / 2, lhs.size(), rhs.size()});
        
        for (auto i = 0; i < n; ++i)
        {
            lhs[i] = in[i * 2];
            rhs[i] = in[i * 2 + 1];
        }
    }
    
    template <class T1, class T2, class T3>
    void deinterleave(const std::vector<std::complex<T1>>& in, std::vector<T2>& lhs, std::vector<T3>& rhs)
    {
        std::vector<float> fin(in.size() * 2);
        for (auto i = 0; i < in.size(); ++i)
        {
            fin[i * 2] = in[i].real();
            fin[i * 2 + 1] = in[i].imag();
        }
        
        deinterleave(fin, lhs, rhs);
    }
}

#endif
