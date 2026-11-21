#include "StepEntry.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("StepEntry: domain behavior and validation") {
    StepEntry value;
    CHECK(value.stride_meters() == .7);
    CHECK(value.remaining(2000) == 1000);
    CHECK(value.remaining(500) == 0);
    CHECK_THROWS_AS(value.remaining(-1), GoalError);
    CHECK_THROWS_AS(StepEntry(0, 0).stride_meters(), GoalError);
    CHECK_THROWS_AS(StepEntry(-1), GoalError);
}
