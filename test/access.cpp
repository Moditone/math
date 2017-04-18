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

TEST_CASE("Access")
{
    std::vector<int> data = { 1, 4, 8, -3, 7, -2 };

    SECTION("throwAccess")
    {
    	for (auto i = 0; i < data.size(); ++i)
    		REQUIRE(math::throwAccess(data.begin(), data.end(), i) == data[i]);

    	REQUIRE_THROWS_AS(math::throwAccess(data.begin(), data.end(), -1), std::out_of_range);
    	REQUIRE_THROWS_AS(math::throwAccess(data.begin(), data.end(), data.size()), std::out_of_range);
    }

    SECTION("constantAccess")
    {
    	for (auto i = 0; i < data.size(); ++i)
    		REQUIRE(math::constantAccess(10)(data.begin(), data.end(), i) == data[i]);

    	REQUIRE(math::constantAccess(10)(data.begin(), data.end(), -1) == 10);
    	REQUIRE(math::constantAccess(10)(data.begin(), data.end(), data.size()) == 10);
    }

    SECTION("clampAccess")
    {
    	for (auto i = 0; i < data.size(); ++i)
    		REQUIRE(math::clampAccess(data.begin(), data.end(), i) == data[i]);

    	REQUIRE(math::clampAccess(data.begin(), data.end(), -1) == data.front());
    	REQUIRE(math::clampAccess(data.begin(), data.end(), data.size()) == data.back());
    }

    SECTION("wrapAccess")
    {
    	for (auto i = 0; i < data.size(); ++i)
    		REQUIRE(math::wrapAccess(data.begin(), data.end(), i) == data[i]);

    	REQUIRE(math::wrapAccess(data.begin(), data.end(), -1) == data.back());
    	REQUIRE(math::wrapAccess(data.begin(), data.end(), data.size()) == data.front());
    }

    SECTION("mirrorAccess")
    {
    	for (auto i = 0; i < data.size(); ++i)
    		REQUIRE(math::mirrorAccess(data.begin(), data.end(), i) == data[i]);

    	REQUIRE(math::mirrorAccess(data.begin(), data.end(), -1) == data[1]);
    	REQUIRE(math::mirrorAccess(data.begin(), data.end(), data.size()) == data[4]);
    }

    SECTION("AccessorFunction")
    {
		math::AccessorFunction<std::vector<int>::iterator> func = math::wrapAccess;

		for (auto i = 0; i < data.size(); ++i)
    		REQUIRE(func(data.begin(), data.end(), i) == data[i]);

    	REQUIRE(func(data.begin(), data.end(), -1) == data.back());
    	REQUIRE(func(data.begin(), data.end(), data.size()) == data.front());
    }
}
