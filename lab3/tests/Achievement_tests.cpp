#include "Achievement.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("Achievement: domain behavior and validation") {
    Achievement value;
    CHECK_FALSE(value.unlocked({}, {}, 6));
    CHECK(value.sessions_remaining({}, 6) == 3);
    CHECK(Achievement("X", 0, 0).unlocked({}, {}, 0));
    CHECK_THROWS_AS(Achievement(""), GoalError);
}
