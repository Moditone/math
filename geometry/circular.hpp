//
//  circular.hpp
//  Math
//
//  Copyright © 2015-2017 Dsperados (info@dsperados.com). All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef MATH_GEOMETRY_CIRCULAR_HPP
#define MATH_GEOMETRY_CIRCULAR_HPP

#include <algorithm>
#include <cmath>
#include <ostream>

#include "../linear/vector.hpp"
#include "rectangular.hpp"

namespace math
{
    //! An n-dimensional circular shape
    template <class T, size_t N>
    class Circular
    {
    public:
        //! Construct a null-circular
        Circular() { }

        //! Construct a circular by providing just the radius (center is 0)
        Circular(const T& radius) :
            radius(radius)
        {

        }

        //! Construct a circular by providing center and radius
        Circular(const Vector<T, N>& center, const T& radius = 0) :
            center(center),
            radius(radius)
        {

        }

        //! Construct from a circular of a different type
        template <class U>
        Circular(const Circular<U, N>& rhs) :
            center(rhs.center),
            radius(rhs.radius)
        {

        }

        //! The diameter of the circular
        auto diameter() const { return radius * 2; }

        //! The rectangular that encompasses the this circular
        Rectangular<T, N> bounds() const
        {
            Rectangular<T, N> bounds;
            bounds.origin = center - radius;
            std::fill_n(bounds.size.begin(), N, diameter());

            return bounds;
        }

    public:
        //! The center of the circle
        Vector<T, N> center;

        //! The radius of the circular
        T radius = 0;
    };

    //! Compare two circulars for equality
    /*! @relates Circular */
    template <class T, class U, std::size_t N>
    bool operator==(const Circular<T, N>& lhs, const Circular<U, N>& rhs)
    {
        return lhs.center == rhs.center && lhs.radius == rhs.radius;
    }

    //! Compare two circulars for inequality
    /*! @relates Circular */
    template <class T, class U, std::size_t N>
    bool operator!=(const Circular<T, N>& lhs, const Circular<U, N>& rhs)
    {
        return !(lhs == rhs);
    }

    //! Write a circular to stream
    /*! @relates Circular */
    template <class T, size_t N>
    std::ostream& operator<<(std::ostream& stream, const Circular<T, N>& circular)
    {
        return stream << "(" << circular.center << ", " << circular.radius << ")";
    }
    
    //! Does a circular contain a point?
    /*! @relates Rectangular */
    template <class T, class U, std::size_t N>
    bool containsInclusive(const Circular<T, N>& circular, const Vector<U, N>& point)
    {
        std::common_type_t<T, U> acc = 0;
        for (auto n = 0; n < N; ++n)
        {
            const auto d = std::fabs(point[n] - circular.center[n]);
            acc += d * d;
        }
        
        return std::sqrt(acc) <= circular.radius;
    }
    
    //! Does a circular contain a point?
    /*! @relates Rectangular */
    template <class T, class U, std::size_t N>
    bool containsExclusive(const Circular<T, N>& circular, const Vector<U, N>& point)
    {
        std::common_type_t<T, U> acc = 0;
        for (auto n = 0; n < N; ++n)
        {
            const auto d = std::fabs(point[n] - circular.center[n]);
            acc += d * d;
        }
        
        return std::sqrt(acc) < circular.radius;
    }
    
    //! Resize a circular
    template <class T, std::size_t N, class U>
    Circular<std::common_type_t<T, U>, N> resize(const Circular<T, N>& circular, const U& factor)
    {
        return {circular.center, circular.radius * factor};
    }

    //! A circle
    template <class T>
    class Circular<T, 2>
    {
    public:
        //! Construct a null-circle
        Circular() { }

        //! Construct a circle by providing just the radius (center is 0)
        Circular(const T& radius) :
            radius(radius)
        {

        }

        //! Construct a circle by providing center and radius
        Circular(const Vector2<T>& center, const T& radius = 0) :
            center(center),
            radius(radius)
        {

        }

        //! Construct from a circle of a different type
        template <class U>
        Circular(const Circular<U, 2>& rhs) :
            center(rhs.center),
            radius(rhs.radius)
        {

        }

        //! The diameter of the circle
        auto diameter() const { return radius * 2; }

        //! The rectangular that encompasses the this circular
        Rectangular<T, 2> bounds() const
        {
            const auto d = diameter();
            return {center - radius, Size2<T>{d, d}};
        }

    public:
        //! The center of the circle
        Vector2<T> center;

        //! The radius of the circle
        T radius = 0;
    };

    //! Convenience alias for circles
    /*! @relates Circular */
    template <class T> using Circle = Circular<T, 2>;
    
    using Circlei = Circle<int>;
    using Circlef = Circle<float>;

    //! The unit circle
    /*! @relates Circular */
    const Circlei UNIT_CIRCLE(1);

    //! A sphere
    template <class T>
    class Circular<T, 3>
    {
    public:
        //! Construct a null-sphere
        Circular() { }

        //! Construct a sphere by providing just the radius (center is 0)
        Circular(const T& radius) :
            radius(radius)
        {

        }

        //! Construct a sphere by providing center and radius
        Circular(const Vector3<T>& center, const T& radius = 0) :
            center(center),
            radius(radius)
        {

        }

        //! Construct from a sphere of a different type
        template <class U>
        Circular(const Circular<U, 3>& rhs) :
            center(rhs.center),
            radius(rhs.radius)
        {

        }

        //! The diameter of the sphere
        auto diameter() const { return radius * 2; }

        //! The rectangular that encompasses the this circular
        Rectangular<T, 3> bounds() const
        {
            const auto d = diameter();
            return {center - radius, Size3<T>{d, d, d}};
        }

    public:
        //! The center of the circle
        Vector3<T> center;

        //! The radius of the sphere
        T radius = 0;
    };

    //! Convenience alias for spheres
    /*! @relates Circular */
    template <class T> using Sphere = Circular<T, 3>;
    
    using Spherei = Sphere<int>;
    using Spheref = Sphere<float>;

    //! The unit sphere
    /*! @relates Circular */
    const Spherei UNIT_SPHERE(1);
}

#endif
