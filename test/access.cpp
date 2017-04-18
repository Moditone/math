//
//  access.cpp
//  Math
//
//  Copyright © 2015-2017 Dsperados (info@dsperados.com). All rights reserved.
//  Licensed under the BSD 3-clause license.
//

#include <vector>

#include "catch.hpp"

#include "../access.hpp"

using namespace math;
using namespace std;

TEST_CASE("Access")
{
    std::vector<int> data = { 1, 4, 8, -3, 7, -2 };

    SECTION("throwAccess")
    {
    	for (auto i = 0; i < data.size(); ++i)
    		REQUIRE(throwAccess(data.begin(), data.end(), i) == data[i]);

    	REQUIRE_THROWS_AS(throwAccess(data.begin(), data.end(), -1), std::out_of_range);
    	REQUIRE_THROWS_AS(throwAccess(data.begin(), data.end(), data.size()), std::out_of_range);
    }

    SECTION("constantAccess")
    {
    	for (auto i = 0; i < data.size(); ++i)
    		REQUIRE(constantAccess(10)(data.begin(), data.end(), i) == data[i]);

    	REQUIRE(constantAccess(10)(data.begin(), data.end(), -1) == 10);
    	REQUIRE(constantAccess(10)(data.begin(), data.end(), data.size()) == 10);
    }

    SECTION("clampAccess")
    {
    	for (auto i = 0; i < data.size(); ++i)
    		REQUIRE(clampAccess(data.begin(), data.end(), i) == data[i]);

    	REQUIRE(clampAccess(data.begin(), data.end(), -1) == data.front());
    	REQUIRE(clampAccess(data.begin(), data.end(), data.size()) == data.back());
    }

    SECTION("wrapAccess")
    {
    	for (auto i = 0; i < data.size(); ++i)
    		REQUIRE(wrapAccess(data.begin(), data.end(), i) == data[i]);

    	REQUIRE(wrapAccess(data.begin(), data.end(), -1) == data.back());
    	REQUIRE(wrapAccess(data.begin(), data.end(), data.size()) == data.front());
    }

    SECTION("mirrorAccess")
    {
    	for (auto i = 0; i < data.size(); ++i)
    		REQUIRE(mirrorAccess(data.begin(), data.end(), i) == data[i]);

    	REQUIRE(mirrorAccess(data.begin(), data.end(), -1) == data[1]);
    	REQUIRE(mirrorAccess(data.begin(), data.end(), data.size()) == data[4]);
    }

    SECTION("AccessorFunction")
    {
		AccessorFunction<std::vector<int>::iterator> func = wrapAccess;

		for (auto i = 0; i < data.size(); ++i)
    		REQUIRE(func(data.begin(), data.end(), i) == data[i]);

    	REQUIRE(func(data.begin(), data.end(), -1) == data.back());
    	REQUIRE(func(data.begin(), data.end(), data.size()) == data.front());
    }
}
