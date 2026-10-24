#include "StepHistory.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("StepHistory: domain behavior and validation") {
    StepHistory value({StepEntry(0, 9000), StepEntry(1, 1000)});
    CHECK(value.total_steps(0, 1) == 10000);
    CHECK(value.total_steps(2, 3) == 0);
    CHECK(value.goal_days() == 1);
    CHECK_THROWS_AS(value.record(StepEntry()), GoalError);
    CHECK_THROWS_AS(value.total_steps(3, 2), GoalError);
    CHECK_THROWS_AS(StepHistory({}, "", 0), GoalError);
}
