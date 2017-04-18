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

using namespace math;
using namespace std;

TEST_CASE("normalize")
{
    SECTION("normalize()")
    {
        SECTION("negative")
        {
            vector<float> x = {0.1, -0.5};
            normalize(x.begin(), x.end(), x.begin());
            
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
                auto peak = *min_element(x.begin(), x.end());
                CHECK(peak == Approx(-1.f));
            }
        }
        
        SECTION("positive")
        {
            vector<float> x = {-0.1, 0.5};
            normalize(x.begin(), x.end(), x.begin());
            
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
                auto peak = *max_element(x.begin(), x.end());
                CHECK(std::abs(peak) == Approx(1.f));
            }
        }
    }
    
    SECTION("normalizeArea()")
    {
        SECTION("Area equal to one")
        {
            vector<float> x{0,5, 1, 0,5};
            normalizeArea(x.begin(), x.end(), x.begin());
            
            auto sum = accumulate(x.begin(), x.end(), 0.f);
            
            CHECK(sum == Approx(1.f));
        }
        
        SECTION("Throw when input has integral of zero")
        {
            vector<float> x{1, -1};
            CHECK_THROWS_AS(normalizeArea(x.begin(), x.end(), x.begin()), std::runtime_error);
        }
    }
    
    
}