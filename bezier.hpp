//
//  bezier.hpp
//  Math
//
//  Copyright © 2015-2017 Dsperados (info@dsperados.com). All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#ifndef DSPERADOS_MATH_BEZIER_HPP
#define DSPERADOS_MATH_BEZIER_HPP

#include "linear/vector.hpp"

namespace math
{
	//! The angle at any point of a quadratic bezier curve
	double quadraticBezierAngle(const double t, const Vector2<float>& control1, const Vector2<float>& control2, const Vector2<float>& point);
}

#endif
