#include "Challenge.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("Challenge: domain behavior and validation") {
    Challenge value("X", StepGoal(1000), "Badge");
    CHECK(value.result(StepHistory(), 0) == "Pending");
    CHECK(value.result(StepHistory({StepEntry()}), 0) == "Badge");
    CHECK(value.steps_missing({}) == 1000);
    CHECK(value.steps_missing(StepHistory({StepEntry()})) == 0);
    CHECK_THROWS_AS(Challenge(""), GoalError);
}
