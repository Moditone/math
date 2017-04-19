//
//  matrix.hpp
//  Math
//
//  Copyright © 2015-2017 Dsperados (info@dsperados.com). All rights reserved.
//  Licensed under the BSD 3-clause license.
//
#ifndef MATH_LINEAR_MATRIX_HPP
#define MATH_LINEAR_MATRIX_HPP

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <ostream>
#include <stdexcept>

#include "vector.hpp"

namespace math
{
	template <typename T, std::size_t C, std::size_t R>
	class Matrix
	{
	public:
		Matrix()
		{
			for (auto& column : data)
				std::fill_n(column, R, 0);
		}

		Matrix(std::initializer_list<Vector<T, R>> columns)
		{
			if (columns.size() > C)
    			throw std::runtime_error("columns.size() >= " + std::to_string(C));

    		std::size_t i = 0;
    		for (auto& column : columns)
    			this->columns[i++] = column;

    		for ( ; i < C; ++i)
    			std::fill_n(this->columns[i].begin(), R, 0);
		}

		template <typename T2>
		Matrix(const Matrix<T2, C, R>& rhs)
		{
			*this = rhs;
		}

		template <typename T2>
		Matrix& operator=(const Matrix<T2, C, R>& rhs)
		{
			for (auto c = 0; c < C; ++c)
				columns[c] = rhs.columns[c];
			return *this;
		}

        template <typename T2>
        Matrix& operator+=(const Matrix<T2, C, R>& rhs)
        {
            return *this = *this + rhs;
        }

        template <typename T2>
        Matrix& operator-=(const Matrix<T2, C, R>& rhs)
        {
            return *this = *this - rhs;
        }

		Vector<T, R>& operator[](std::size_t index)
        {
        	assert(index < C);
            return columns[index];
        }

		const Vector<T, R>& operator[](std::size_t index) const
        {
        	assert(index < C);
            return columns[index];
        }

        Vector<T, C> getRow(std::size_t index) const
        {
        	assert(index < R);

        	Vector<T, C> row;
        	for (auto i = 0; i < C; ++i)
        		row[i] = columns[i][index];

        	return row;
        }

        void setRow(std::size_t index, const Vector<T, C>& row)
        {
        	assert(index < R);

        	for (auto i = 0; i < C; ++i)
        		columns[i][index] = row[i];
        }

	public:
		union
		{
            //! The elements of the matrix in column-major order
			T data[C][R];

            //! The elements of the matrix as column vectors
            Vector<T, R> columns[C];
		};
	};

// --- Free functions --- //

    //! Compare two matrices of arbitrary size
    template <typename T1, typename T2, std::size_t C, std::size_t R>
    bool operator==(const Matrix<T1, C, R>& lhs, const Matrix<T2, C, R>& rhs)
    {
        for (auto c = 0; c < C; ++c)
        {
            if (lhs.columns[c] != rhs.columns[c])
                return false;
        }

        return true;
    }

    //! Compare two matrices of arbitrary size
    template <typename T1, typename T2, std::size_t C, std::size_t R>
    bool operator!=(const Matrix<T1, C, R>& lhs, const Matrix<T2, C, R>& rhs)
    {
        return !(lhs == rhs);
    }

    //! Add two matrices together
    template <typename T1, typename T2, std::size_t C, std::size_t R>
    auto operator+(const Matrix<T1, C, R>& lhs, const Matrix<T2, C, R>& rhs)
    {
        Matrix<std::common_type_t<T1, T2>, C, R> result;

        for (auto c = 0; c < C; ++c)
        {
            for (auto r = 0; r < R; ++r)
                result[c][r] = lhs[c][r] + rhs[c][r];
        }
        
        return result;
    }

    //! Subtract a matrix from another
    template <typename T1, typename T2, std::size_t C, std::size_t R>
    auto operator-(const Matrix<T1, C, R>& lhs, const Matrix<T2, C, R>& rhs)
    {
        Matrix<std::common_type_t<T1, T2>, C, R> result;

        for (auto c = 0; c < C; ++c)
        {
            for (auto r = 0; r < R; ++r)
                result[c][r] = lhs[c][r] - rhs[c][r];
        }
        
        return result;
    }

    //! Multiply a matrix by a matrix
	template <typename T1, typename T2, std::size_t C, std::size_t CR, std::size_t R>
	auto operator*(const Matrix<T1, C, CR>& lhs, const Matrix<T2, CR, R>& rhs)
    {
        Matrix<std::common_type_t<T1, T2>, C, R> result;

        for (auto c = 0; c < C; ++c)
        {
        	for (auto r = 0; r < R; ++r)
        	{
        		result[c][r] = 0;
        		
        		for (auto i = 0; i < CR; ++i)
        			result[c][r] += lhs[i][r] * rhs[c][i];
        	}
        }
        
        return result;
    }

    //! Multiply a matrix by a vector
    template <typename T1, typename T2, std::size_t C, std::size_t R>
    auto operator*(const Matrix<T1, C, R>& lhs, const Vector<T2, C>& rhs)
    {
    	Vector<std::common_type_t<T1, T2>, C> result;

        for (auto r = 0; r < R; ++r)
        {
        	result[r] = 0;

        	for (auto c = 0; c < C; ++c)
        		result[r] += lhs[c][r] * rhs[c];
        }
        
        return result;
    }

    //! Write a matrix to an output stream
    template <typename T, std::size_t C, std::size_t R>
    std::ostream& operator<<(std::ostream& stream, const Matrix<T, C, R>& matrix)
    {
    	stream << "(";
    	for (auto c = 0; c < C - 1; ++c)
    		stream << matrix[c] << ", ";
    	stream << matrix[C - 1] << ")";

    	return stream;
    }

// --- Square matrix --- //

    template <typename T, std::size_t N>
    class Matrix<T, N, N>
    {
    public:
        Matrix()
        {
            for (auto& column : data)
                std::fill_n(column, N, 0);
        }

        //! Construct the matrix by filling the diagonal axis with a vector
        Matrix(const Vector<T, N>& diagonal) :
            Matrix()
        {
            for (auto i = 0; i < N; ++i)
                data[i][i] = diagonal[i];
        }

        //! Construct the matrix by filling the diagonal axis with a constant value
        Matrix(const T& diagonal) :
            Matrix()
        {
            for (auto i = 0; i < N; ++i)
                data[i][i] = diagonal;
        }

        Matrix(std::initializer_list<Vector<T, N>> columns)
        {
            if (columns.size() > N)
                throw std::runtime_error("columns.size() >= " + std::to_string(N));

            std::size_t i = 0;
            for (auto& column : columns)
                this->columns[i++] = column;

            for ( ; i < N; ++i)
                std::fill_n(this->columns[i].begin(), N, 0);
        }

        template <typename T2>
        Matrix(const Matrix<T2, N, N>& rhs)
        {
            *this = rhs;
        }

        //! Copy from a smaller matrix
        template <typename T2, std::size_t N2>
        Matrix(const Matrix<T2, N2, N2>& rhs, const std::enable_if_t<(N2 < N), T>& diagonal)
        {
            std::size_t c = 0;
            for (; c < N2; ++c)
            {
                std::size_t r = 0;
                for (; r < N2; ++r)
                    data[c][r] = rhs[c][r];

                for (; r < N; ++r)
                    data[c][r] = (c == r) ? diagonal : 0;
            }

            for (; c < N; ++c)
            {
                for (std::size_t r = 0; r < N; ++r)
                    data[c][r] = (c == r) ? diagonal : 0;
            }
        }

        template <typename T2>
        Matrix& operator=(const Matrix<T2, N, N>& rhs)
        {
            for (auto c = 0; c < N; ++c)
                columns[c] = rhs.columns[c];
            return *this;
        }

        template <typename T2>
        Matrix& operator+=(const Matrix<T2, N, N>& rhs)
        {
            return *this = *this + rhs;
        }

        template <typename T2>
        Matrix& operator-=(const Matrix<T2, N, N>& rhs)
        {
            return *this = *this - rhs;
        }

        template <typename T2>
        Matrix& operator*=(const Matrix<T2, N, N>& rhs)
        {
            return *this = *this * rhs;
        }

        Vector<T, N>& operator[](std::size_t index)
        {
            assert(index < N);
            return columns[index];
        }

        const Vector<T, N>& operator[](std::size_t index) const
        {
            assert(index < N);
            return columns[index];
        }

        Vector<T, N> getRow(std::size_t index) const
        {
            assert(index < N);

            Vector<T, N> row;
            for (auto i = 0; i < N; ++i)
                row[i] = columns[i][index];

            return row;
        }

        void setRow(std::size_t index, const Vector<T, N>& row)
        {
            assert(index < N);

            for (auto i = 0; i < N; ++i)
                columns[i][index] = row[i];
        }

    public:
        //! The identity matrix for a square matrix of this size
        static const Matrix IDENTITY;

    public:
        union
        {
            //! The elements of the matrix in column-major order
            T data[N][N];

            //! The elements of the matrix as column vectors
            Vector<T, N> columns[N];
        };
    };

    //! The identity matrix for square matrices
    template <typename T, std::size_t N>
    const Matrix<T, N, N> Matrix<T, N, N>::IDENTITY = Matrix<T, N, N>(1);

// --- Convenient matrix aliases --- //

	template <typename T> using Matrix2x2 = Matrix<T, 2, 2>;
    template <typename T> using Matrix2 = Matrix2x2<T>;

	template <typename T> using Matrix3x3 = Matrix<T, 3, 3>;
    template <typename T> using Matrix3 = Matrix3x3<T>;

	template <typename T> using Matrix4x4 = Matrix<T, 4, 4>;
    template <typename T> using Matrix4 = Matrix4x4<T>;

// --- Operator specializations --- //

    template <typename T1, typename T2>
    Matrix2<std::common_type_t<T1, T2>> operator+(const Matrix2<T1>& lhs, const Matrix2<T2>& rhs)
    {
        return {{ lhs[0][0] + rhs[0][0], lhs[0][1] + rhs[0][1] },
                { lhs[1][0] + rhs[1][0], lhs[1][1] + rhs[1][1] }};
    }

    template <typename T1, typename T2>
    Matrix3<std::common_type_t<T1, T2>> operator+(const Matrix3<T1>& lhs, const Matrix3<T2>& rhs)
    {
        return {{ lhs[0][0] + rhs[0][0], lhs[0][1] + rhs[0][1], lhs[0][2] + rhs[0][2] },
                { lhs[1][0] + rhs[1][0], lhs[1][1] + rhs[1][1], lhs[1][2] + rhs[1][2] },
                { lhs[2][0] + rhs[2][0], lhs[2][1] + rhs[2][1], lhs[2][2] + rhs[2][2] }};
    }

    template <typename T1, typename T2>
    Matrix2<std::common_type_t<T1, T2>> operator-(const Matrix2<T1>& lhs, const Matrix2<T2>& rhs)
    {
        return {{ lhs[0][0] - rhs[0][0], lhs[0][1] - rhs[0][1] },
                { lhs[1][0] - rhs[1][0], lhs[1][1] - rhs[1][1] }};
    }

    template <typename T1, typename T2>
    Matrix3<std::common_type_t<T1, T2>> operator-(const Matrix3<T1>& lhs, const Matrix3<T2>& rhs)
    {
        return {{ lhs[0][0] - rhs[0][0], lhs[0][1] - rhs[0][1], lhs[0][2] - rhs[0][2] },
                { lhs[1][0] - rhs[1][0], lhs[1][1] - rhs[1][1], lhs[1][2] - rhs[1][2] },
                { lhs[2][0] - rhs[2][0], lhs[2][1] - rhs[2][1], lhs[2][2] - rhs[2][2] }};
    }

    template <typename T1, typename T2>
    Matrix2<std::common_type_t<T1, T2>> operator*(const Matrix2<T1>& lhs, const Matrix2<T2>& rhs)
    {
        return {{ lhs[0][0] * rhs[0][0] + lhs[1][0] * rhs[0][1],
                  lhs[0][1] * rhs[0][0] + lhs[1][1] * rhs[0][1] },
                { lhs[0][0] * rhs[1][0] + lhs[1][0] * rhs[1][1],
                  lhs[0][1] * rhs[1][0] + lhs[1][1] * rhs[1][1] }};
    }

    template <typename T1, typename T2>
    Matrix3<std::common_type_t<T1, T2>> operator*(const Matrix3<T1>& lhs, const Matrix3<T2>& rhs)
    {
        return {{ lhs[0][0] * rhs[0][0] + lhs[1][0] * rhs[0][1] + lhs[2][0] * rhs[0][2],
                  lhs[0][1] * rhs[0][0] + lhs[1][1] * rhs[0][1] + lhs[2][1] * rhs[0][2],
                  lhs[0][2] * rhs[0][0] + lhs[2][1] * rhs[0][1] + lhs[2][2] * rhs[0][2] },

                { lhs[0][0] * rhs[1][0] + lhs[1][0] * rhs[1][1] + lhs[2][0] * rhs[1][2],
                  lhs[0][1] * rhs[1][0] + lhs[1][1] * rhs[1][1] + lhs[2][1] * rhs[1][2],
                  lhs[0][2] * rhs[1][0] + lhs[2][1] * rhs[1][1] + lhs[2][2] * rhs[1][2] },

                { lhs[0][0] * rhs[2][0] + lhs[1][0] * rhs[2][1] + lhs[2][0] * rhs[2][2],
                  lhs[0][1] * rhs[2][0] + lhs[1][1] * rhs[2][1] + lhs[2][1] * rhs[2][2],
                  lhs[0][2] * rhs[2][0] + lhs[2][1] * rhs[2][1] + lhs[2][2] * rhs[2][2] }};
    }
}

#endif /* mat_h */
