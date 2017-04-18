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


TEST_CASE("Sigmoid")
{
    SECTION("sigmoid")
    {
        CHECK(math::sigmoid(-1, 1, 1) == Approx(-1));
        CHECK(math::sigmoid(0, 1, 1) == 0);
        CHECK(math::sigmoid(1, 1, 1) == Approx(1));
    }
    
    SECTION("sigmoidTan")
    {
        CHECK(math::sigmoidTan(-1, 1, 1) == Approx(-1));
        CHECK(math::sigmoidTan(0, 1, 1) == 0);
        CHECK(math::sigmoidTan(1, 1, 1) == Approx(1));
    }
    
    SECTION("sigmoidExp")
    {
        CHECK(math::sigmoidExp(-1, 1, 1) == Approx(-1));
        CHECK(math::sigmoidExp(0, 1, 1) == 0);
        CHECK(math::sigmoidExp(1, 1, 1) == Approx(1));
    }
    
    SECTION("throw for distortion factor <= 0")
    {
        CHECK_THROWS_AS(math::sigmoid(0, 0, 0), std::runtime_error);
        CHECK_THROWS_AS(math::sigmoidTan(0, 0, 0), std::runtime_error);
        CHECK_THROWS_AS(math::sigmoidExp(0, 0, 0), std::runtime_error);
    }
}
