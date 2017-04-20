//
//  rectangular.hpp
//  Math
//
//  Copyright © 2015-2017 Dsperados (info@dsperados.com). All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef MATH_GEOMETRY_RECTANGULAR_HPP
#define MATH_GEOMETRY_RECTANGULAR_HPP

#include <algorithm>
#include <cmath>
#include <numeric>
#include <ostream>

#include "../linear/vector.hpp"
#include "size.hpp"

namespace math
{
    //! An n-dimensional rectangular shape
    template <class T, size_t N>
    class Rectangular
    {
    public:
        //! Construct a null-rectangular
        Rectangular() { }

        //! Construct a rectangular by providing just the size (origin = 0)
        Rectangular(const Size<T, N>& size) :
            size(size)
        {

        }

        //! Construct a rectangular by providing origin and size
        Rectangular(const Vector<T, N>& origin, const Size<T, N>& size = {}) :
            origin(origin),
            size(size)
        {

        }

        //! Construct a rectangular by providing origin and the outer edge
        Rectangular(const Vector<T, N>& origin, const Vector<T, N>& edge = {}) :
            origin(origin)
        {
            outer(edge);
        }

        //! Construct from a rectangular of a different type
        template <class U>
        Rectangular(const Rectangular<U, N>& rhs) :
            origin(rhs.origin),
            size(rhs.size)
        {

        }

        //! The center of the rectangular
        auto center() const
        {
            return origin + size / 2.0;
        }

        //! The volume of the rectangular
        T volume() const
        {
            return std::accumulate(size.begin(), size.end(), T{1}, [](const auto& lhs, const auto& rhs){ return lhs * rhs; });
        }

        //! Set the outer edge
        void outer(const Vector<T, N>& outer)
        {
            std::transform(origin.begin(), origin.end(), outer.begin(), size.begin(), [](auto lhs, auto rhs){ return rhs - lhs; });
        }

        //! The outer edge
        Vector<T, N> outer() const { return origin + size; }

    public:
        //! The origin of the rectangular
        Vector<T, N> origin;

        //! The size of the rectangular
        Size<T, N> size;
    };

    //! Compare two rectangulars for equality
    /*! @relates Rectangular */
    template <class T, class U, std::size_t N>
    bool operator==(const Rectangular<T, N>& lhs, const Rectangular<U, N>& rhs)
    {
        return lhs.origin == rhs.origin && lhs.size == rhs.size;
    }

    //! Compare two rectangulars for inequality
    /*! @relates Rectangular */
    template <class T, class U, std::size_t N>
    bool operator!=(const Rectangular<T, N>& lhs, const Rectangular<U, N>& rhs)
    {
        return !(lhs == rhs);
    }

    //! Write a rectangular to stream
    /*! @relates Rectangular */
    template <class T, size_t N>
    std::ostream& operator<<(std::ostream& stream, const Rectangular<T, N>& rectangular)
    {
        return stream << "(" << rectangular.origin << ", " << rectangular.size << ")";
    }
    
    //! Normalize a rectangular
    template <class T, std::size_t N>
    Rectangular<T, N> normalize(Rectangular<T, N> rect)
    {
        for (auto n = 0; n < N; ++n)
        {
            if (rect.size[n] < 0)
            {
                rect.size[n] = -rect.size[n];
                rect.origin[n] -= rect.size[n];
            }
        }
        
        return rect;
    }
    
    //! Does a rectangular contain a point?
    /*! @relates Rectangular */
    template <class T, class U, std::size_t N>
    bool containsExclusive(const Rectangular<T, N>& rect, const Vector<U, N>& point)
    {
        const auto r = normalize(rect);
        for (auto n = 0; n < N; ++n)
        {
            if (point[n] < r.origin[n] || r.outer()[n] <= point[n])
                return false;
        }
        
        return true;
    }

    //! Does a rectangular contain a point?
    /*! @relates Rectangular */
    template <class T, class U, std::size_t N>
    bool containsInclusive(const Rectangular<T, N>& rect, const Vector<U, N>& point)
    {
        const auto r = normalize(rect);
        for (auto n = 0; n < N; ++n)
        {
            if (point[n] < r.origin[n] || r.outer()[n] < point[n])
                return false;
        }

        return true;
    }
    
    //! Does a rectangular contain another?
    /*! @relates Rectangular */
    template <class T, class U, std::size_t N>
    bool containsExclusive(const Rectangular<T, N>& rect1, const Rectangular<U, N>& rect2)
    {
        return containsExclusive(rect1, rect2.origin) && containsExclusive(rect1, rect2.outer());
    }
    
    //! Does a rectangular contain another?
    /*! @relates Rectangular */
    template <class T, class U, std::size_t N>
    bool containsInclusive(const Rectangular<T, N>& rect1, const Rectangular<U, N>& rect2)
    {
        return containsInclusive(rect1, rect2.origin) && containsInclusive(rect1, rect2.outer());
    }

    //! Do two rectangulars intersect?
    /*! @relates Rectangular */
    template <class T, class U, std::size_t N>
    bool intersectsExclusive(const Rectangular<T, N>& rect1, const Rectangular<U, N>& rect2)
    {
        const auto r1 = normalize(rect1);
        const auto r2 = normalize(rect2);

        for (auto n = 0; n < N; ++n)
        {
            if (((r1.origin[n] < r2.origin[n]) || (r1.origin[n] >= r2.outer()[n])) &&
                ((r2.origin[n] < r1.origin[n]) || (r2.origin[n] >= r1.outer()[n])))
            {
                return false;
            }
        }

        return true;
    }

    //! Do two rectangulars intersect?
    /*! @relates Rectangular */
    template <class T, class U, std::size_t N>
    bool intersectsInclusive(const Rectangular<T, N>& rect1, const Rectangular<U, N>& rect2)
    {
        const auto r1 = normalize(rect1);
        const auto r2 = normalize(rect2);

        for (auto n = 0; n < N; ++n)
        {
            if (((r1.origin[n] < r2.origin[n]) || (r1.origin[n] > r2.outer()[n])) &&
                ((r2.origin[n] < r1.origin[n]) || (r2.origin[n] > r1.outer()[n])))
            {
                return false;
            }
        }

        return true;
    }
    
    //! Move a rectangular
    template <class T, std::size_t N, class U>
    Rectangular<std::common_type_t<T, U>, N> move(const Rectangular<T, N>& rect, const Size<U, N>& distance)
    {
        return {rect.origin + distance, rect.size};
    }
    
    //! Move a rectangular
    template <class T, std::size_t N, class U>
    Rectangular<std::common_type_t<T, U>, N> move(const Rectangular<T, N>& rect, const Vector<U, N>& distance)
    {
        return {rect.origin + distance, rect.size};
    }
    
    //! Resize a rectangular
    template <class T, std::size_t N, class U>
    Rectangular<std::common_type_t<T, U>, N> resize(const Rectangular<T, N>& rect, const U& factor)
    {
        return {rect.origin, rect.size * factor};
    }

    //! Expand a rectangular
    /*! @relates Rectangular */
    template <class T, std::size_t N, class U>
    auto expand(const Rectangular<T, N>& rect, const Size<U, N>& expansion)
    {
        Rectangular<std::common_type_t<T, U>, N> result = rect;
        
        for (auto i = 0; i < N; ++i)
        {
            if (result.size[i] < 0)
            {
                result.origin[i] += expansion[i];
                result.size[i] -= expansion[i] * 2;
            } else {
                result.origin[i] -= expansion[i];
                result.size[i] += expansion[i] * 2;
            }
        }
        
        return result;
    }

    //! Expand a rectangular to contain a point
    /*! @relates Rectangular */
    template <class T, class U, std::size_t N>
    auto expand(const Rectangular<T, N>& rect, const Vector<U, N>& point)
    {
        Rectangular<std::common_type_t<T, U>, N> result;

        for (auto n = 0; n < N; ++n)
        {
            result.origin[n] = std::min(point[n], rect.origin[n]);
            result.origin[n] = std::max(point[n], rect.origin[n] + rect.size[n]) - result.origin[n];
        }

        return result;
    }

    //! Expand a rectangular to contain another
    /*! @relates Rectangular */
    template <class T, class U, std::size_t N>
    auto expand(const Rectangular<T, N>& rect, const Rectangular<U, N>& rhs)
    {
        return expand(expand(rect, rhs.origin), rhs.outer());
    }

    //! Reduce a rectangular
    /*! @relates Rectangular */
    template <class T, std::size_t N, class U>
    auto reduce(const Rectangular<T, N>& rect, const Size<U, N>& reduction)
    {
        return expand(rect, -reduction);
    }

    //! The intersection of two rectangulars
    /*! The intersection is the rectangular that both lhs and rhs have in common
        @relates Rectangular */
    template <class T, class U, std::size_t N>
    Rectangular<T, N> intersect(const Rectangular<T, N>& lhs, const Rectangular<U, N>& rhs)
    {
        Rectangular<std::common_type_t<T, U>, N> intersection;
        for (auto i = 0; i < N; ++i)
        {
            intersection.origin[i] = std::max<T>(lhs.origin[i], rhs.origin[i]);
            intersection.size[i] = std::min<T>(lhs.origin[i] + lhs.size[i], rhs.origin[i] + rhs.size[i]) - intersection.origin[i];
        }

        return intersection;
    }

    //! A rectangle
    template <class T>
    class Rectangular<T, 2>
    {
    public:
        //! Construct a null-rectangle
        Rectangular() { }

        //! Construct a rectangle by providing just the size (origin = 0)
        Rectangular(const Size2<T>& size) :
            size(size)
        {

        }

        //! Construct a rectangle by providing origin and size
        Rectangular(const Vector2<T>& origin, const Size2<T>& size = {}) :
            origin(origin),
            size(size)
        {

        }

        //! Construct a rectangle by providing origin and the outer edge
        Rectangular(const Vector2<T>& origin, const Vector2<T>& edge = {}) :
            origin(origin)
        {
            outer(edge);
        }

        //! Construct from a rectangle of a different type
        template <class U>
        Rectangular(const Rectangular<U, 2>& rhs) :
            origin(rhs.origin),
            size(rhs.size)
        {

        }

        //! The center of the rectangle
        auto center() const
        {
            return origin + size / 2.0;
        }

        //! The surface of the box
        T surface() const
        {
            return size.width * size.height;
        }

        //! X of the origin
        auto& x1() const { return origin.x; }

        //! Y of the origin
        auto& y1() const { return origin.y; }

        //! Set x of the outer edge
        void x2(const T& value) { size.width = value - origin.x; }

        //! X of the outer edge
        auto x2() const { return origin.x + size.width; }

        //! Set y of the outer edge
        void y2(const T& value) { size.height = value - origin.y; }

        //! Y of the outer edge
        auto y2() const { return origin.y + size.height; }

        //! Set the outer edge
        void outer(const Vector2<T>& outer)
        {
            size.width = outer.x - origin.x;
            size.height = outer.y - origin.y;
        }

        //! The outer edge
        Vector2<T> outer() const { return origin + size; }

    public:
        //! The origin of the rectangle
        Vector2<T> origin;

        //! The size of the rectangle
        Size2<T> size;
    };
    
    //! Expand a rectangle
    /*! @relates Rectangular */
    template <class T, class U, class V>
    auto expand(const Rectangular<T, 2>& rect, const U& horizontal, const V& vertical)
    {
        return expand(rect, Size2<std::common_type_t<U, V>>(horizontal, vertical));
    }
    
    //! Reduce a rectangle
    /*! @relates Rectangular */
    template <class T, class U, class V>
    auto reduce(const Rectangular<T, 2>& rect, const U& horizontal, const V& vertical)
    {
        return reduce(rect, Size2<std::common_type_t<U, V>>(horizontal, vertical));
    }

    //! Convenience alias for rectangles
    /*! @relates Rectangular */
    template <class T> using Rectangle = Rectangular<T, 2>;
    
    using Rectanglei = Rectangle<int>;
    using Rectanglef = Rectangle<float>;

    //! The unit rectangle
    /*! @relates Rectangular */
    const Rectanglei UNIT_RECTANGLE(Size2i(1, 1));

    //! A box
    template <class T>
    class Rectangular<T, 3>
    {
    public:
        //! Construct a null-box
        Rectangular() { }

        //! Construct a box by providing just the size (origin = 0)
        Rectangular(const Size3<T>& size) :
            size(size)
        {

        }

        //! Construct a box by providing origin and size
        Rectangular(const Vector3<T>& origin, const Size3<T>& size = {}) :
            origin(origin),
            size(size)
        {

        }

        //! Construct a box by providing origin and the outer edge
        Rectangular(const Vector3<T>& origin, const Vector3<T>& edge = {}) :
            origin(origin)
        {
            outer(edge);
        }

        //! Construct from a box of a different type
        template <class U>
        Rectangular(const Rectangular<U, 3>& rhs) :
            origin(rhs.origin),
            size(rhs.size)
        {

        }

        //! The center of the box
        auto center() const
        {
            return origin + size / 2.0;
        }

        //! The volume of the box
        T volume() const
        {
            return size.width * size.height * size.depth;
        }

        //! X of the origin
        auto& x1() const { return origin.x; }

        //! Y of the origin
        auto& y1() const { return origin.y; }

        //! Z of the origin
        auto& z1() const { return origin.z; }

        //! Set x of the outer edge
        void x2(const T& value) { size.width = value - origin.x; }

        //! X of the outer edge
        auto x2() const { return origin.x + size.width; }

        //! Set y of the outer edge
        void y2(const T& value) { size.height = value - origin.y; }

        //! Y of the outer edge
        auto y2() const { return origin.y + size.height; }

        //! Set z of the outer edge
        void z2(const T& value) { size.depth = value - origin.z; }

        //! Z of the outer edge
        auto z2() const { return origin.z + size.depth; }

        //! Set the outer edge
        void outer(const Vector3<T>& outer)
        {
            size.width = outer.x - origin.x;
            size.height = outer.y - origin.y;
            size.depth = outer.z - origin.z;
        }

        //! The outer edge
        Vector3<T> outer() const { return origin + size; }

    public:
        //! The origin of the box
        Vector3<T> origin;

        //! The size of the box
        Size3<T> size;
    };
    
    //! Convenience alias for boxes
    /*! @relates Rectangular */
    template <class T> using Box = Rectangular<T, 3>;
    
    using Boxi = Box<int>;
    using Boxf = Box<float>;

    //! The unit box
    /*! @relates Rectangular */
    const Boxi UNIT_BOX(Size3<int>(1, 1, 1));
}

#endif
