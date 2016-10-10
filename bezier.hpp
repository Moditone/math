#ifndef DSPERADOS_MATH_BEZIER_HPP
#define DSPERADOS_MATH_BEZIER_HPP

#include <dsperados/geometry/point.hpp>

namespace math
{
	//! The angle at any point of a quadratic bezier curve
	double quadraticBezierAngle(const double t, const geo::Point2f& control1, const geo::Point2f& control2, const geo::Point2f& point);
}

#endif