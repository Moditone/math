//
//  bezier.hpp
//  Math
//
//  Copyright © 2015-2018 Moditone (info@moditone.com). All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef MODITONE_MATH_BEZIER_HPP
#define MODITONE_MATH_BEZIER_HPP

#include <cmath>

#include "linear/vector.hpp"

namespace math
{
	//! The angle at any point of a quadratic bezier curve
	template <typename T>
	double quadraticBezierAngle(const double t, const Vector2<T>& control1, const Vector2<T>& control2, const Vector2<T>& point)
	{
		const auto invt = 1 - t;
        
        const auto c1 = -3 * invt * invt;
        const auto c2 = 3 * invt * invt * -6 * t * invt;
        const auto c3 = -3 * t * t + 6 * t * invt;
        const auto c4 = 3 * t * t;
        
        const auto dx = (c1 * 0) + (c2 * control1.x) + (c3 * control2.x) + (c4 * point.x);
        const auto dy = (c1 * 0) + (c2 * control1.y) + (c3 * control2.y) + (c4 * point.y);
        
        return std::atan2(dx, dy);
	}
}

#endif
