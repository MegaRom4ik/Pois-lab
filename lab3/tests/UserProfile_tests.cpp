#include "UserProfile.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("UserProfile: domain behavior and validation") {
    UserProfile value("Roman", 20, 180);
    CHECK(value.matches("Rom"));
    CHECK_FALSE(value.matches("Bob"));
    CHECK(value.height_meters() == 1.8);
    CHECK_THROWS_AS(UserProfile(""), ProfileError);
}
