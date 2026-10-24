#include "WorkoutPlan.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("WorkoutPlan: domain behavior and validation") {
    WorkoutPlan value;
    value.add(Workout("Lift", {StrengthExercise(Exercise(), {ExerciseSet()})}));
    CHECK(value.planned_sessions() == 4);
    CHECK(value.planned_volume() == 800);
    CHECK_THROWS_AS(WorkoutPlan("", {}, 0), PlanError);
}
