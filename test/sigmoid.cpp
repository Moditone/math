//
//  sigmoid.cpp
//  Math
//
//  Copyright © 2015-2017 Dsperados (info@dsperados.com). All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#include <stdexcept>

#include "catch.hpp"

#include "../sigmoid.hpp"

using namespace math;
using namespace std;

TEST_CASE("Sigmoid")
{
    SECTION("sigmoid")
    {
        CHECK(sigmoid(-1, 1, 1) == Approx(-1));
        CHECK(sigmoid(0, 1, 1) == 0);
        CHECK(sigmoid(1, 1, 1) == Approx(1));
    }
    
    SECTION("sigmoidTan")
    {
        CHECK(sigmoidTan(-1, 1, 1) == Approx(-1));
        CHECK(sigmoidTan(0, 1, 1) == 0);
        CHECK(sigmoidTan(1, 1, 1) == Approx(1));
    }
    
    SECTION("sigmoidExp")
    {
        CHECK(sigmoidExp(-1, 1, 1) == Approx(-1));
        CHECK(sigmoidExp(0, 1, 1) == 0);
        CHECK(sigmoidExp(1, 1, 1) == Approx(1));
    }
    
    SECTION("throw for distortion factor <= 0")
    {
        CHECK_THROWS_AS(sigmoid(0, 0, 0), std::runtime_error);
        CHECK_THROWS_AS(sigmoidTan(0, 0, 0), std::runtime_error);
        CHECK_THROWS_AS(sigmoidExp(0, 0, 0), std::runtime_error);
    }
}
