//
//  size.hpp
//  Geometry
//
//  Created by Stijn Frishert (info@stijnfrishert.com) on 14/05/16.
//  Copyright © 2015-2016 Stijn Frishert. All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef MATH_GEOMETRY_SIZE_HPP
#define MATH_GEOMETRY_SIZE_HPP

#include <algorithm>
#include <functional>
#include <ostream>
#include <utility>

#include "../linear/vector.hpp"

namespace math
{
    //! An n-dimensional size
    template <class T, std::size_t N>
    class Size
    {
    public:
        //! Construct a null-size
        Size()
        {
            for (std::size_t i = 0; i < N; ++i)
                data[i] = T{};
        }

        //! Construct by passing the sizes
        template <typename... Args>
        Size(Args&&... elements) : data{std::forward<Args&&>(elements)...} { }

        //! Construct by passing a size of another type
        template <class U>
        Size(const Size<U, N>& rhs) { operator=(rhs); }

        //! Assign from a size of another type
        template <class U>
        Size& operator=(const Size<U, N>& rhs)
        {
            std::copy_n(rhs.begin(), N, data.begin());

            return *this;
        }

        //! Add and reassign
        template <class U>
        Size& operator+=(const U& rhs)
        {
            return *this = *this + rhs;
        }

        //! Add and reassign
        template <class U>
        Size& operator-=(const U& rhs)
        {
            return *this = *this - rhs;
        }

        //! Multiply and reassign
        template <class U>
        Size& operator*=(const U& rhs)
        {
            return *this = *this * rhs;
        }

        //! Divide and reassign
        template <class U>
        Size& operator/=(const U& rhs)
        {
            return *this = *this / rhs;
        }

        //! Access one of the axes
        T& operator[](std::size_t index) { return data[index]; }

        //! Access one of the axes
        const T& operator[](std::size_t index) const { return data[index]; }

    private:
        T data[N];
    };

    //! Compare two sizes for equality
    /*! @relates Size */
    template <class T, class U, std::size_t N>
    bool operator==(const Size<T, N>& lhs, const Size<U, N>& rhs)
    {
        for (std::size_t i = 0; i < N; ++i)
        {
            if (lhs[i] != rhs[i])
                return false;
        }
        
        return true;
    }

    //! Compare two sizes for inequality
    /*! @relates Size */
    template <class T, class U, std::size_t N>
    bool operator!=(const Size<T, N>& lhs, const Size<U, N>& rhs)
    {
        return !(lhs == rhs);
    }

    //! Negate a size
    /*! @relates Size */
    template <class T, std::size_t N>
    auto operator-(const Size<T, N>& size)
    {
        auto result = size;
        for (auto i = 0; i < N; ++i)
            result[i] = -size.data[i];

        return result;
    }

    //! Add two sizes together
    /*! @relates Size */
    template <class T, class U, std::size_t N>
    auto operator+(const Size<T, N>& lhs, const Size<U, N>& rhs)
    {
        Size<std::common_type_t<T, U>, N> y;
        for (auto i = 0; i < N; ++i)
            y[i] = lhs.data[i] + rhs.data[i];

        return y;
    }

    //! Add a scalar to all size elements
    /*! @relates Size */
    template <class T, class U, std::size_t N>
    auto operator+(const Size<T, N>& lhs, const U& rhs)
    {
        Size<std::common_type_t<T, U>, N> y;
        for (auto i = 0; i < N; ++i)
            y[i] = lhs.data[i] + rhs;

        return y;
    }

    //! Subtract two sizes from each other
    /*! @relates Size */
    template <class T, class U, std::size_t N>
    auto operator-(const Size<T, N>& lhs, const Size<U, N>& rhs)
    {
        Size<std::common_type_t<T, U>, N> y;
        for (auto i = 0; i < N; ++i)
            y[i] = lhs.data[i] - rhs.data[i];

        return y;
    }

    //! Subtract a scalar from all size elements
    /*! @relates Size */
    template <class T, class U, std::size_t N>
    auto operator-(const Size<T, N>& lhs, const U& rhs)
    {
        Size<std::common_type_t<T, U>, N> y;
        for (auto i = 0; i < N; ++i)
            y[i] = lhs.data[i] - rhs;

        return y;
    }

    //! Multiply a size by a scalar
    /*! @relates Size */
    template <class T, class U, std::size_t N>
    auto operator*(const Size<T, N>& lhs, const U& rhs)
    {
        Size<std::common_type_t<T, U>, N> y;
        for (auto i = 0; i < N; ++i)
            y[i] = lhs.data[i] * rhs;

        return y;
    }

    //! Multiply a size by a scalar
    /*! @relates Size */
    template <class T, class U, std::size_t N>
    auto operator*(const T& lhs, const Size<U, N>& rhs)
    {
        Size<std::common_type_t<T, U>, N> y;
        for (auto i = 0; i < N; ++i)
            y[i] = lhs * rhs.data[i];

        return y;
    }

    //! Multiply a size by another
    /*! @relates Size */
    template <class T, class U, std::size_t N>
    auto operator*(const Size<T, N>& lhs, const Size<U, N>& rhs)
    {
        Size<std::common_type_t<T, U>, N> y;
        for (auto i = 0; i < N; ++i)
            y[i] = lhs.data[i] * rhs.data[i];

        return y;
    }

    //! Divide a size by a scalar
    /*! @relates Size */
    template <class T, class U, std::size_t N>
    auto operator/(const Size<T, N>& lhs, const U& rhs)
    {
        Size<std::common_type_t<T, U>, N> y;
        for (auto i = 0; i < N; ++i)
            y[i] = lhs.data[i] / rhs;

        return y;
    }

    //! Divide a size by another
    /*! @relates Size */
    template <class T, class U, std::size_t N>
    auto operator/(const Size<T, N>& lhs, const Size<U, N>& rhs)
    {
        Size<std::common_type_t<T, U>, N> y;
        for (auto i = 0; i < N; ++i)
            y[i] = lhs.data[i] / rhs;

        return y;
    }

    //! Write a Size to stream
    /*! @relates Size */
    template <class T, size_t N>
    std::ostream& operator<<(std::ostream& stream, const Size<T, N>& size)
    {
        stream << '(';
        for (std::size_t i = 0; i < N; ++i)
        {
            stream << size[i];
            if (i < N - 1)
                stream << ", ";
        }
        return stream << ')';
    }

    //! A 2-dimensional size
    template <class T>
    class Size<T, 2>
    {
    public:
        //! Construct a null-size
        Size()
        {
            width = T{};
            height = T{};
        }

        //! Construct by passing the sizes
        Size(const T& width, const T& height) : width(width), height(height) { }

        //! Construct by passing a size of another type
        template <class U>
        Size(const Size<U, 2>& rhs) { operator=(rhs); }

        //! Assign from a size of another type
        template <class U>
        Size& operator=(const Size<U, 2>& rhs)
        {
            width = rhs.width;
            height = rhs.height;

            return *this;
        }

        //! Add and reassign
        template <class U>
        Size& operator+=(const U& rhs)
        {
            return *this = *this + rhs;
        }

        //! Add and reassign
        template <class U>
        Size& operator-=(const U& rhs)
        {
            return *this = *this - rhs;
        }

        //! Multiply and reassign
        template <class U>
        Size& operator*=(const U& rhs)
        {
            return *this = *this * rhs;
        }

        //! Divide and reassign
        template <class U>
        Size& operator/=(const U& rhs)
        {
            return *this = *this / rhs;
        }

        //! Access one of the axes
        T& operator[](std::size_t index)
        {
            switch (index)
            {
                case 0: return width;
                case 1: return height;
                default: throw std::out_of_range("Out of bounds Size2[]");
            }
        }

        //! Access one of the axes
        const T& operator[](std::size_t index) const
        {
            switch (index)
            {
                case 0: return width;
                case 1: return height;
                default: throw std::out_of_range("Out of bounds Size2[]");
            }
        }

        //! Return the elements as array
        std::array<T, 2> asArray() const { return {{width, height}}; }

    public:
        union
        {
            T data[2];
            struct { T width; T height; };
        };
    };

    //! Convenience alias for 2-dimensional sizes
    /*! @relates Size */
    template <class T>
    using Size2 = Size<T, 2>;
    
    using Size2i = Size2<int>;
    using Size2f = Size2<float>;

    //! A 3-dimensional size
    template <class T>
    class Size<T, 3>
    {
    public:
        //! Construct a null-size
        Size()
        {
            width = T{};
            height = T{};
            depth = T{};
        }

        //! Construct by passing the sizes
        Size(const T& width, const T& height, const T& depth) : width(width), height(height), depth(depth) { }

        //! Construct by passing a size of another type
        template <class U>
        Size(const Size<U, 3>& rhs) { operator=(rhs); }

        //! Assign from a size of another type
        template <class U>
        Size& operator=(const Size<U, 3>& rhs)
        {
            width = rhs.width;
            height = rhs.height;
            depth = rhs.depth;

            return *this;
        }

        //! Add and reassign
        template <class U>
        Size& operator+=(const U& rhs)
        {
            return *this = *this + rhs;
        }

        //! Add and reassign
        template <class U>
        Size& operator-=(const U& rhs)
        {
            return *this = *this - rhs;
        }

        //! Multiply and reassign
        template <class U>
        Size& operator*=(const U& rhs)
        {
            return *this = *this * rhs;
        }

        //! Divide and reassign
        template <class U>
        Size& operator/=(const U& rhs)
        {
            return *this = *this / rhs;
        }

        //! Access one of the axes
        T& operator[](std::size_t index)
        {
            switch (index)
            {
                case 0: return width;
                case 1: return height;
                case 2: return depth;
                default: throw std::out_of_range("Out of bounds Size3[]");
            }
        }

        //! Access one of the axes
        const T& operator[](std::size_t index) const
        {
            switch (index)
            {
                case 0: return width;
                case 1: return height;
                case 2: return depth;
                default: throw std::out_of_range("Out of bounds Size3[]");
            }
        }

        //! Return the elements as array
        std::array<T, 3> asArray() const { return {{width, height, depth}}; }

    public:
        union
        {
            T data[3];
            struct { T width; T height; T depth; };
        };
    };

    //! Convenience alias for 3-dimensional sizes
    /*! @relates Size */
    template <class T>
    using Size3 = Size<T, 3>;
    
    using Size3i = Size3<int>;
    using Size3f = Size3<float>;

    // --- Point/Size arithmetic --- //

    //! Move a point by a size
    /*! @relates Point
     @relates Size */
    template <class T, class U, std::size_t N>
    auto operator+(const Vector<T, N>& lhs, const Size<U, N>& rhs)
    {
        Vector<std::common_type_t<T, U>, N> y;
        for (auto i = 0; i < N; ++i)
            y.data[i] = lhs[i] + rhs[i];

        return y;
    }

    //! Move a point by a size
    /*! @relates Point
     @relates Size */
    template <class T, class U, std::size_t N>
    auto operator-(const Vector<T, N>& lhs, const Size<U, N>& rhs)
    {
        Vector<std::common_type_t<T, U>, N> y;
        for (auto i = 0; i < N; ++i)
            y.data[i] = lhs[i] - rhs[i];

        return y;
    }
}

#endif
