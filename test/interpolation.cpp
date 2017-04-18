//
//  interpolation.cpp
//  Math
//
//  Copyright © 2015-2017 Dsperados (info@dsperados.com). All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#include <vector>

#include "catch.hpp"

#include "../interpolation.hpp"

using namespace math;
using namespace std;

TEST_CASE("Interpolation")
{
    SECTION("Free functions")
    {
        REQUIRE(interpolateNearest(0.25, 4, 6) == Approx(4));
        REQUIRE(interpolateLinear(0.25, 4, 6) == Approx(4.5));
        REQUIRE(interpolateCosine(0.25, 4, 6) == Approx(4.2928932188));
        REQUIRE(interpolateCubic(0.25, 3, 4, 6, 7) == Approx(4.59375));
        REQUIRE(interpolateCatmullRom(0.25, 3, 4, 6, 7) == Approx(4.453125));
        REQUIRE(interpolateHermite(0.25, 3, 4, 6, 7, 0.5, 0.5) == Approx(4.359375));
    }

    std::vector<int> data = { 1, 4, 8, -3, 7, -2 };

    SECTION("lambda's")
    {
        REQUIRE(nearestInterpolation(data.begin(), data.end(), 1.25, clampAccess) == Approx(4));
        REQUIRE(linearInterpolation(data.begin(), data.end(), 1.25, clampAccess) == Approx(5));
        REQUIRE(cosineInterpolation(data.begin(), data.end(), 1.25, clampAccess) == Approx(4.5857864376));
        REQUIRE(cubicInterpolation(data.begin(), data.end(), 1.25, clampAccess) == Approx(5.9375));
        REQUIRE(catmullRomInterpolation(data.begin(), data.end(), 1.25, clampAccess) == Approx(5.28125));
        REQUIRE(hermiteInterpolation(0.5, 0.5)(data.begin(), data.end(), 1.25, clampAccess) == Approx(4.84765625));
    }

    SECTION("InterpolationFunction")
    {
		InterpolationFunction<std::vector<int>::iterator> func = linearInterpolation;
        REQUIRE(func(data.begin(), data.end(), 1.25, clampAccess) == 5);
    }
}
