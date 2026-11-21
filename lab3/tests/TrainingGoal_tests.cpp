#include "TrainingGoal.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("TrainingGoal: domain behavior and validation") {
    TrainingGoal value;
    CHECK(value.sessions_missing({}) == 3);
    CHECK(value.completion_percent({}) == 0);
    WorkoutLog log({WorkoutSession(1, Workout("X", {}, {CardioActivity()}), 0, true)});
    CHECK(TrainingGoal(1).sessions_missing(log) == 0);
    CHECK(TrainingGoal(1).completion_percent(log) == 100);
    CHECK_THROWS_AS(TrainingGoal(0), GoalError);
}
