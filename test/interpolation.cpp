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

TEST_CASE("Interpolation")
{
    SECTION("Free functions")
    {
        REQUIRE(math::interpolateNearest(0.25, 4, 6) == Approx(4));
        REQUIRE(math::interpolateLinear(0.25, 4, 6) == Approx(4.5));
        REQUIRE(math::interpolateCosine(0.25, 4, 6) == Approx(4.2928932188));
        REQUIRE(math::interpolateCubic(0.25, 3, 4, 6, 7) == Approx(4.59375));
        REQUIRE(math::interpolateCatmullRom(0.25, 3, 4, 6, 7) == Approx(4.453125));
        REQUIRE(math::interpolateHermite(0.25, 3, 4, 6, 7, 0.5, 0.5) == Approx(4.359375));
    }

    std::vector<int> data = { 1, 4, 8, -3, 7, -2 };

    SECTION("lambda's")
    {
        REQUIRE(math::nearestInterpolation(data.begin(), data.end(), 1.25, math::clampAccess) == Approx(4));
        REQUIRE(math::linearInterpolation(data.begin(), data.end(), 1.25, math::clampAccess) == Approx(5));
        REQUIRE(math::cosineInterpolation(data.begin(), data.end(), 1.25, math::clampAccess) == Approx(4.5857864376));
        REQUIRE(math::cubicInterpolation(data.begin(), data.end(), 1.25, math::clampAccess) == Approx(5.9375));
        REQUIRE(math::catmullRomInterpolation(data.begin(), data.end(), 1.25, math::clampAccess) == Approx(5.28125));
        REQUIRE(math::hermiteInterpolation(0.5, 0.5)(data.begin(), data.end(), 1.25, math::clampAccess) == Approx(4.84765625));
    }

    SECTION("InterpolationFunction")
    {
		math::InterpolationFunction<std::vector<int>::iterator> func = math::linearInterpolation;
        REQUIRE(func(data.begin(), data.end(), 1.25, math::clampAccess) == 5);
    }
}
