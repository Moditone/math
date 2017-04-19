//
//  triangular.hpp
//  Geometry
//
//  Created by Stijn Frishert (info@stijnfrishert.com) on 17/06/16.
//  Copyright © 2015-2016 Stijn Frishert. All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef MATH_GEOMETRY_TRIANGULAR_HPP
#define MATH_GEOMETRY_TRIANGULAR_HPP

#include <array>
#include <algorithm>
#include <initializer_list>

#include "../linear/vector.hpp"

namespace math
{
    //! An n-dimensional triangular shape
    template <class T, std::size_t N>
    class Triangular
    {
    public:
        //! Construct an empty triangular
        constexpr Triangular() = default;
        
        //! Construct a triangular by passing its points
        constexpr Triangular(std::initializer_list<Vector<T, N>> points)
        {
            std::move(points.begin(), std::next(points.begin(), std::min(points.size(), N + 1)), this->points.begin());
        }
        
        //! Access one of the points of the triangular
        constexpr auto& operator[](std::size_t index) { return points[index]; }
        
        //! Access one of the points of the triangular
        constexpr const auto& operator[](std::size_t index) const { return points[index]; }
        
        // Begin and end for ranged for-loops
        auto begin() { return points.begin(); }
        auto begin() const { return points.begin(); }
        auto end() { return points.end(); }
        auto end() const { return points.end(); }
        
    public:
        //! The points of the triangular, as an array
        std::array<Vector<T, N>, N + 1> points;
    };
    
    //! Compute the centroid of a triangular
    template <class T, std::size_t N>
    constexpr Vector<double, N> centroid(const Triangular<T, N>& triangular)
    {
        return std::accumulate(triangular.begin(), triangular.end(), 0) / static_cast<double>(N);
    }
    
    //! Move a triangular
    template <class T, std::size_t N, class U>
    constexpr auto move(const Triangular<T, N>& triangular, const Size<U, N>& distance)
    {
        Triangular<std::common_type_t<T, U>, N> result = triangular;
        
        for (auto& point : result)
            point += distance;
        
        return result;
    }
    
    template <class T>
    using Triangle = Triangular<T, 2>;
    
    using Trianglei = Triangle<int>;
    using Trianglef = Triangle<float>;
    
    template <class T>
    using Pyramid = Triangular<T, 3>;
    
    using Pyramidi = Pyramid<int>;
    using Pyramidf = Pyramid<float>;
}

#endif
