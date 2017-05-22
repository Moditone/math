//
//  interleave.cpp
//  Math
//
//  Copyright © 2015-2017 Dsperados (info@dsperados.com). All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#include <vector>

#include "catch.hpp"

#include "../interleave.hpp"

TEST_CASE("Interleave")
{
    SECTION("Interleave")
    {
        std::vector<float> a = { 1, 2 };
        std::vector<float> b = { 3, 4 };
        std::vector<float> c(4);

        math::interleave(a.begin(), a.end(), b.begin(), c.begin());

        REQUIRE(c[0] == 1);
        REQUIRE(c[1] == 3);
        REQUIRE(c[2] == 2);
        REQUIRE(c[3] == 4);
    }

    SECTION("Deinterleave")
    {
        std::vector<float> a = { 1, 2, 3, 4, 5, 6, 7, 8 };
        std::vector<float> b(a.size() / 2);
        std::vector<float> c(a.size() / 2);

        math::deinterleave(a.begin(), a.end(), b.begin(), c.begin());

        REQUIRE(b[0] == 1);
        REQUIRE(b[1] == 3);
        REQUIRE(b[2] == 5);
        REQUIRE(b[3] == 7);
        REQUIRE(c[0] == 2);
        REQUIRE(c[1] == 4);
        REQUIRE(c[2] == 6);
        REQUIRE(c[3] == 8);
    }
}
