#include "ActivitySummary.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("ActivitySummary: domain behavior and validation") {
    WorkoutSession session(1, Workout("X", {}, {CardioActivity()}), 0);
    session.finish();
    ActivitySummary value(WorkoutLog({session}), StepHistory({StepEntry(0, 14000)}), 6);
    CHECK(value.weekly_sessions() == 1);
    CHECK(value.weekly_step_average() == 2000);
    CHECK(ActivitySummary({}, StepHistory({StepEntry()}), 0).weekly_step_average() == 1000);
    CHECK_THROWS_AS(ActivitySummary({}, {}, -1), GoalError);
}
