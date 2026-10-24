#include "WorkoutSession.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("WorkoutSession: domain behavior and validation") {
    CHECK_THROWS_AS(WorkoutSession(1, Workout(), 0, true), WorkoutError);
    WorkoutSession value(1, Workout("Run", {}, {CardioActivity()}), 2);
    CHECK_FALSE(value.in_period(0, 3));
    value.finish();
    CHECK(value.in_period(2, 2));
    CHECK_FALSE(value.in_period(3, 4));
    CHECK_THROWS_AS(value.finish(), WorkoutError);
    CHECK_THROWS_AS(value.in_period(4, 3), WorkoutError);
    CHECK_THROWS_AS(WorkoutSession().finish(), WorkoutError);
    CHECK_THROWS_AS(WorkoutSession(0), WorkoutError);
}
