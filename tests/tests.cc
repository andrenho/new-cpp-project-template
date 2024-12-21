#include "doctest.h"

TEST_SUITE("example")
{
    TEST_CASE("example test")
    {
        SUBCASE("subcase")
        {
            size_t i = 9;
            CHECK(i == 9);
        }
    }
}