//
//  translate.hpp
//  Math
//
//  Copyright © 2015-2017 Dsperados (info@dsperados.com). All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef BEAR_GRAPHICS_TRANSLATE_HPP
#define BEAR_GRAPHICS_TRANSLATE_HPP

#include <moditone/math/linear/matrix.hpp>
#include <moditone/math/linear/vector.hpp>

namespace bear::graphics
{
	template <typename T>
	math::Matrix4<T> translation(const T& x, const T& y, const T& z)
	{
		auto mat = math::Matrix4<T>::IDENTITY;
		mat[3][0] = x;
		mat[3][1] = y;
		mat[3][2] = z;
		
		return mat;
	}

	template <typename T>
	math::Matrix4<T> translation(const math::Vector3<T>& position)
	{
		return translation(position.x, position.y, position.z);
	}

	template <typename T>
	math::Vector3<T> getTranslation(const math::Matrix4<T>& matrix)
	{
		return {matrix[3][0], matrix[3][1], matrix[3][2]};
	}
}

#endif
