//
//  normalize.cpp
//  Math
//
//  Copyright © 2015-2017 Dsperados (info@dsperados.com). All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#include <algorithm>
#include <stdexcept>
#include <vector>

#include "catch.hpp"

#include "../normalize.hpp"

TEST_CASE("normalize")
{
    SECTION("normalize()")
    {
        SECTION("negative")
        {
            std::vector<float> x = {0.1, -0.5};
            math::normalize(x.begin(), x.end(), x.begin());
            
            SECTION("values in bounds")
            {
                for (auto& value: x)
                {
                    CHECK(value <= 1);
                    CHECK(value >= -1);
                }
            }
            
            SECTION("peak equals -1")
            {
                auto peak = *std::min_element(x.begin(), x.end());
                CHECK(peak == Approx(-1.f));
            }
        }
        
        SECTION("positive")
        {
            std::vector<float> x = {-0.1, 0.5};
            math::normalize(x.begin(), x.end(), x.begin());
            
            SECTION("values in bounds")
            {
                for (auto& value: x)
                {
                    CHECK(value <= 1);
                    CHECK(value >= -1);
                }
            }
            
            SECTION("peak equals 1")
            {
                auto peak = *std::max_element(x.begin(), x.end());
                CHECK(std::abs(peak) == Approx(1.f));
            }
        }
    }
    
    SECTION("normalizeArea()")
    {
        SECTION("Area equal to one")
        {
            std::vector<float> x{0,5, 1, 0,5};
            math::normalizeArea(x.begin(), x.end(), x.begin());
            
            auto sum = std::accumulate(x.begin(), x.end(), 0.f);
            
            CHECK(sum == Approx(1.f));
        }
        
        SECTION("Throw when input has integral of zero")
        {
            std::vector<float> x{1, -1};
            CHECK_THROWS_AS(math::normalizeArea(x.begin(), x.end(), x.begin()), std::runtime_error);
        }
    }
    
    
}