//
//  vector.hpp
//  Math
//
//  Copyright © 2015-2017 Dsperados (info@dsperados.com). All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <initializer_list>
#include <ostream>
#include <stdexcept>
#include <string>

namespace math
{
	//! Generic multi-dimensional vector class
	template <typename T, std::size_t N>
    class Vector
    {
    public:
        using value_type = T;
        
    public:
        Vector() :
            Vector(T{0})
        {
            
        }

        template <typename T2>
    	Vector(std::initializer_list<T2> elements)
    	{
    		if (elements.size() > N)
    			throw std::runtime_error("elements.size() >= " + std::to_string(N));

    		std::move(elements.begin(), elements.end(), data);
            const auto left = N - elements.size();
            std::fill_n(data + N - left, left, T(0));
    	}

        template <typename T2>
        Vector(const T2& value)
        {
            std::fill_n(data.begin(), N, value);
        }

        template <typename T2>
        Vector(const Vector<T2, N>& rhs)
        {
        	*this = rhs;
        }

        template <typename T2>
        Vector& operator=(const Vector<T2, N>& rhs)
        {
            std::transform(rhs.begin(), rhs.end(), data, [](const T2& x){ return static_cast<T>(x); });
            return *this;
        }
        
        template <typename T2>
        Vector& operator+=(const Vector<T2, N>& rhs)
        {
    		return *this = *this + rhs;
        }

        template <typename T2>
        Vector& operator+=(const T2& rhs)
        {
    		return *this = *this + rhs;
        }

        template <typename T2>
        Vector& operator-=(const Vector<T2, N>& rhs)
        {
    		return *this = *this - rhs;
        }

        template <typename T2>
        Vector& operator-=(const T2& rhs)
        {
    		return *this = *this - rhs;
        }

        template <typename T2>
        Vector& operator*=(const Vector<T2, N>& rhs)
        {
    		return *this = *this * rhs;
        }

        template <typename T2>
        Vector& operator*=(const T2& rhs)
        {
    		return *this = *this * rhs;
        }

        template <typename T2>
        Vector& operator/=(const Vector<T2, N>& rhs)
        {
    		return *this = *this / rhs;
        }

        template <typename T2>
        Vector& operator/=(const T2& rhs)
        {
    		return *this = *this / rhs;
        }

		T& operator[](std::size_t index)
        {
            assert(index < N);
            return data[index];
        }
        
        const T& operator[](std::size_t index) const
        {
            assert(index < N);
            return data[index];
        }

        auto begin() { return data; }
        auto begin() const { return data; }
        auto cbegin() const { return data; }

        auto end() { return data + N; }
        auto end() const { return data + N; }
        auto cend() const { return data + N; }
        
	public:
    	T data[N];
    };

// --- Free functions --- //

    template <typename T1, typename T2, std::size_t N>
    bool operator==(const Vector<T1, N>& lhs, const Vector<T2, N>& rhs)
    {
    	for (auto i = 0; i < N; ++i)
    	{
    		if (lhs[i] != rhs[i])
    			return false;
    	}

    	return true;
    }

    template <typename T1, typename T2, std::size_t N>
    bool operator!=(const Vector<T1, N>& lhs, const Vector<T2, N>& rhs)
    {
    	return !(lhs == rhs);
    }

    template <typename T1, typename T2, std::size_t N>
    auto operator+(const Vector<T1, N>& lhs, const Vector<T2, N>& rhs)
    {
    	Vector<std::common_type_t<T1, T2>, N> result;
    	std::transform(lhs.begin(), lhs.end(), rhs.begin(), result.begin(), std::plus<>());
    	return result;
    }

    template <typename T1, typename T2, std::size_t N>
    auto operator+(const Vector<T1, N>& lhs, const T2& rhs)
    {
    	Vector<std::common_type_t<T1, T2>, N> result = lhs;
    	for (auto& element : result)
    		element += rhs;
    	return result;
    }

    template <typename T1, typename T2, std::size_t N>
    auto operator+(const T2& lhs, const Vector<T1, N>& rhs)
    {
    	Vector<std::common_type_t<T1, T2>, N> result = rhs;
    	for (auto& element : result)
    		element += lhs;
    	return result;
    }

    template <typename T1, typename T2, std::size_t N>
    auto operator-(const Vector<T1, N>& lhs, const Vector<T2, N>& rhs)
    {
    	Vector<std::common_type_t<T1, T2>, N> result;
    	std::transform(lhs.begin(), lhs.end(), rhs.begin(), result.begin(), std::minus<>());
    	return result;
    }

    template <typename T1, typename T2, std::size_t N>
    auto operator-(const Vector<T1, N>& lhs, const T2& rhs)
    {
    	Vector<std::common_type_t<T1, T2>, N> result = lhs;
    	for (auto& element : result)
    		element -= rhs;
    	return result;
    }

    template <typename T, std::size_t N>
    auto operator-(const Vector<T, N>& vec)
    {
    	Vector<T, N> result;
    	std::transform(vec.begin(), vec.end(), result.begin(), std::negate<>());
    	return result;
    }

    template <typename T1, typename T2, std::size_t N>
    auto operator*(const Vector<T1, N>& lhs, const Vector<T2, N>& rhs)
    {
    	Vector<std::common_type_t<T1, T2>, N> result;
    	std::transform(lhs.begin(), lhs.end(), rhs.begin(), result.begin(), std::multiplies<>());
    	return result;
    }

    template <typename T1, typename T2, std::size_t N>
    auto operator*(const Vector<T1, N>& lhs, const T2& rhs)
    {
    	Vector<std::common_type_t<T1, T2>, N> result = lhs;
    	for (auto& element : result)
    		element *= rhs;
    	return result;
    }

    template <typename T1, typename T2, std::size_t N>
    auto operator*(const T2& lhs, const Vector<T1, N>& rhs)
    {
    	Vector<std::common_type_t<T1, T2>, N> result = rhs;
    	for (auto& element : result)
    		element *= lhs;
    	return result;
    }

    template <typename T1, typename T2, std::size_t N>
    auto operator/(const Vector<T1, N>& lhs, const Vector<T2, N>& rhs)
    {
    	Vector<std::common_type_t<T1, T2>, N> result;
    	std::transform(lhs.begin(), lhs.end(), rhs.begin(), result.begin(), std::divides<>());
    	return result;
    }

    template <typename T1, typename T2, std::size_t N>
    auto operator/(const Vector<T1, N>& lhs, const T2& rhs)
    {
    	Vector<std::common_type_t<T1, T2>, N> result = lhs;
    	for (auto& element : result)
    		element /= rhs;
    	return result;
    }

	template <typename T, std::size_t N>
    std::ostream& operator<<(std::ostream& stream, const Vector<T, N>& vec)
    {
    	stream << "(";
    	for (auto i = 0; i < N - 1; ++i)
    		stream << vec[i] << ", ";
    	stream << vec[N - 1] << ")";

    	return stream;
    }

// --- Vector2 --- //

    template <typename T>
    class Vector<T, 2>
    {
	public:
        
        using value_type = T;
        
    	Vector() = default;

        template <typename T2>
    	Vector(std::initializer_list<T2> elements)
    	{
    		if (elements.size() > 2)
    			throw std::runtime_error("elements.size() >= 2");

    		std::move(elements.begin(), elements.end(), data);
            const auto left = 2 - elements.size();
            std::fill_n(data + 2 - left, left, T(0));
    	}

        Vector(const T& value) :
        	x(value), y(value)
        {
            
        }

        Vector(const T& x, const T& y) :
        	x(x), y(y)
        {
            
        }

        template <typename T2>
        Vector(const Vector<T2, 2>& rhs)
        {
        	*this = rhs;
        }

        template <typename T2>
        Vector& operator=(const Vector<T2, 2>& rhs)
        {
            x = static_cast<T>(rhs.x);
            y = static_cast<T>(rhs.y);
            return *this;
        }
        
        template <typename T2>
        Vector& operator+=(const Vector<T2, 2>& rhs)
        {
    		return *this = *this + rhs;
        }

        template <typename T2>
        Vector& operator+=(const T2& rhs)
        {
    		return *this = *this + rhs;
        }

        template <typename T2>
        Vector& operator-=(const Vector<T2, 2>& rhs)
        {
    		return *this = *this - rhs;
        }

        template <typename T2>
        Vector& operator-=(const T2& rhs)
        {
    		return *this = *this - rhs;
        }

        template <typename T2>
        Vector& operator*=(const Vector<T2, 2>& rhs)
        {
    		return *this = *this * rhs;
        }

        template <typename T2>
        Vector& operator*=(const T2& rhs)
        {
    		return *this = *this * rhs;
        }

        template <typename T2>
        Vector& operator/=(const Vector<T2, 2>& rhs)
        {
    		return *this = *this / rhs;
        }

        template <typename T2>
        Vector& operator/=(const T2& rhs)
        {
    		return *this = *this / rhs;
        }

		T& operator[](std::size_t index)
        {
            assert(index < 2);
            return data[index];
        }
        
        const T& operator[](std::size_t index) const
        {
            assert(index < 2);
            return data[index];
        }

        auto begin() { return data; }
        auto begin() const { return data; }
        auto cbegin() const { return data; }

        auto end() { return data + 2; }
        auto end() const { return data + 2; }
        auto cend() const { return data + 2; }

    public:
        // Convenience directional vectors
        static const Vector UP;
        static const Vector DOWN;
        static const Vector LEFT;
        static const Vector RIGHT;
        
	public:
    	union
        {
            struct { T x, y; };
            struct { T u, v; };
            struct { T s, t; };
            T data[2] = { 0, 0 };
        };
    };

    template <typename T>
    using Vector2 = Vector<T, 2>;

    template <typename T> const Vector2<T> Vector2<T>::UP(0, 1);
    template <typename T> const Vector2<T> Vector2<T>::DOWN(0, -1);
    template <typename T> const Vector2<T> Vector2<T>::LEFT(-1, 0);
    template <typename T> const Vector2<T> Vector2<T>::RIGHT(1, 0);

// --- Vector3 --- //

    template <typename T>
    class Vector<T, 3>
    {
	public:
        
        using value_type = T;
        
    	Vector() = default;

        template <typename T2>
    	Vector(std::initializer_list<T2> elements)
    	{
    		if (elements.size() > 3)
    			throw std::runtime_error("elements.size() >= 3");

    		std::move(elements.begin(), elements.end(), data);
            const auto left = 3 - elements.size();
            std::fill_n(data + 3 - left, left, T(0));
    	}

        Vector(const T& value) :
        	x(value), y(value), z(value)
        {
            
        }

        Vector(const T& x, const T& y, const T& z) :
        	x(x), y(y), z(z)
        {
            
        }

        template <typename T2>
        Vector(const Vector<T2, 2>& rhs, const T& z) :
            z(z)
        {
            x = static_cast<T>(rhs.x);
            y = static_cast<T>(rhs.y);
        }

        template <typename T2>
        Vector(const Vector<T2, 3>& rhs)
        {
        	*this = rhs;
        }

        template <typename T2>
        Vector& operator=(const Vector<T2, 3>& rhs)
        {
            x = static_cast<T>(rhs.x);
            y = static_cast<T>(rhs.y);
            z = static_cast<T>(rhs.z);
            return *this;
        }
        
        template <typename T2>
        Vector& operator+=(const Vector<T2, 3>& rhs)
        {
    		return *this = *this + rhs;
        }

        template <typename T2>
        Vector& operator+=(const T2& rhs)
        {
    		return *this = *this + rhs;
        }

        template <typename T2>
        Vector& operator-=(const Vector<T2, 3>& rhs)
        {
    		return *this = *this - rhs;
        }

        template <typename T2>
        Vector& operator-=(const T2& rhs)
        {
    		return *this = *this - rhs;
        }

        template <typename T2>
        Vector& operator*=(const Vector<T2, 3>& rhs)
        {
    		return *this = *this * rhs;
        }

        template <typename T2>
        Vector& operator*=(const T2& rhs)
        {
    		return *this = *this * rhs;
        }

        template <typename T2>
        Vector& operator/=(const Vector<T2, 3>& rhs)
        {
    		return *this = *this / rhs;
        }

        template <typename T2>
        Vector& operator/=(const T2& rhs)
        {
    		return *this = *this / rhs;
        }

		T& operator[](std::size_t index)
        {
            assert(index < 3);
            return data[index];
        }
        
        const T& operator[](std::size_t index) const
        {
            assert(index < 3);
            return data[index];
        }

        auto begin() { return data; }
        auto begin() const { return data; }
        auto cbegin() const { return data; }

        auto end() { return data + 3; }
        auto end() const { return data + 3; }
        auto cend() const { return data + 3; }

    public:
        // Convenience directional vectors
        static const Vector UP;
        static const Vector DOWN;
        static const Vector LEFT;
        static const Vector RIGHT;
        static const Vector FORWARD;
        static const Vector BACKWARD;
        
	public:
    	union
        {
            struct { T x, y, z; };
            struct { T u, v, w; };
            struct { T r, g, b; };
            T data[3] = { 0, 0, 0 };
        };
    };

    template <typename T>
    using Vector3 = Vector<T, 3>;

    template <typename T> const Vector3<T> Vector3<T>::UP(0, 1, 0);
    template <typename T> const Vector3<T> Vector3<T>::DOWN(0, -1, 0);
    template <typename T> const Vector3<T> Vector3<T>::LEFT(-1, 0, 0);
    template <typename T> const Vector3<T> Vector3<T>::RIGHT(1, 0, 0);
    template <typename T> const Vector3<T> Vector3<T>::FORWARD(0, 0, 1);
    template <typename T> const Vector3<T> Vector3<T>::BACKWARD(0, 0, -1);

// --- Vector4 --- //

    template <typename T>
    class Vector<T, 4>
    {
	public:
        
        using value_type = T;
        
    	Vector() = default;

        template <typename T2>
    	Vector(std::initializer_list<T2> elements)
    	{
    		if (elements.size() > 4)
    			throw std::runtime_error("elements.size() >= 4");

    		std::move(elements.begin(), elements.end(), data);
            const auto left = 4 - elements.size();
            std::fill_n(data + 4 - left, left, T(0));
    	}

        Vector(const T& value) :
        	x(value), y(value), z(value), w(value)
        {
            
        }

        Vector(const T& x, const T& y, const T& z, const T& w) :
        	x(x), y(y), z(z), w(w)
        {
            
        }

        template <typename T2>
        Vector(const Vector<T2, 2>& rhs, const T& z, const T& w) :
            z(z), w(w)
        {
            x = static_cast<T>(rhs.x);
            y = static_cast<T>(rhs.y);
        }

        template <typename T2>
        Vector(const Vector<T2, 3>& rhs, const T& w) :
            w(w)
        {
            x = static_cast<T>(rhs.x);
            y = static_cast<T>(rhs.y);
            z = static_cast<T>(rhs.z);
        }

        template <typename T2>
        Vector(const Vector<T2, 4>& rhs)
        {
        	*this = rhs;
        }

        template <typename T2>
        Vector& operator=(const Vector<T2, 4>& rhs)
        {
            x = static_cast<T>(rhs.x);
            y = static_cast<T>(rhs.y);
            z = static_cast<T>(rhs.z);
            w = static_cast<T>(rhs.w);
            return *this;
        }
        
        template <typename T2>
        Vector& operator+=(const Vector<T2, 4>& rhs)
        {
    		return *this = *this + rhs;
        }

        template <typename T2>
        Vector& operator+=(const T2& rhs)
        {
    		return *this = *this + rhs;
        }

        template <typename T2>
        Vector& operator-=(const Vector<T2, 4>& rhs)
        {
    		return *this = *this - rhs;
        }

        template <typename T2>
        Vector& operator-=(const T2& rhs)
        {
    		return *this = *this - rhs;
        }

        template <typename T2>
        Vector& operator*=(const Vector<T2, 4>& rhs)
        {
    		return *this = *this * rhs;
        }

        template <typename T2>
        Vector& operator*=(const T2& rhs)
        {
    		return *this = *this * rhs;
        }

        template <typename T2>
        Vector& operator/=(const Vector<T2, 4>& rhs)
        {
    		return *this = *this / rhs;
        }

        template <typename T2>
        Vector& operator/=(const T2& rhs)
        {
    		return *this = *this / rhs;
        }

		T& operator[](std::size_t index)
        {
            assert(index < 4);
            return data[index];
        }
        
        const T& operator[](std::size_t index) const
        {
            assert(index < 4);
            return data[index];
        }

        auto begin() { return data; }
        auto begin() const { return data; }
        auto cbegin() const { return data; }

        auto end() { return data + 4; }
        auto end() const { return data + 4; }
        auto cend() const { return data + 4; }
        
	public:
    	union
        {
            struct { T x, y, z, w; };
            struct { T r, g, b, a; };
            T data[4] = { 0, 0, 0, 0 };
        };
    };

    template <typename T>
    using Vector4 = Vector<T, 4>;
}
