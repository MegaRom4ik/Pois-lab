#include "StepGoal.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("StepGoal: domain behavior and validation") {
    StepGoal value(1000, 0, 2);
    StepHistory history({StepEntry(0, 1000)});
    CHECK(value.progress(history) == 1);
    CHECK(value.achieved(history, 1));
    CHECK_FALSE(value.achieved(history, 3));
    CHECK_FALSE(value.achieved(StepHistory(), 1));
    CHECK(StepGoal().progress(StepHistory()) == 0);
    CHECK_THROWS_AS(StepGoal(0), GoalError);
}
