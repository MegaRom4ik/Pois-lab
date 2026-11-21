#include "WorkoutLog.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("WorkoutLog: domain behavior and validation") {
    WorkoutLog value;
    WorkoutSession session(1, Workout("Lift", {StrengthExercise(Exercise(), {ExerciseSet()})}), 2);
    CHECK_THROWS_AS(value.append(session), WorkoutError);
    session.finish();
    value.append(session);
    CHECK(value.volume_between(0, 3) == 200);
    CHECK(value.volume_between(4, 5) == 0);
    CHECK(value.count_between(2, 2) == 1);
    CHECK(value.count_between(4, 5) == 0);
    CHECK_THROWS_AS(value.append(session), WorkoutError);
    CHECK_THROWS_AS(value.count_between(3, 2), WorkoutError);
    CHECK_THROWS_AS(value.volume_between(-1, 2), WorkoutError);
    CHECK_THROWS_AS(WorkoutLog({}, "", 1), WorkoutError);
    CHECK(WorkoutLog({session}).sessions().size() == 1);
    CHECK_THROWS_AS(WorkoutLog({session}, "X", 1).append(WorkoutSession(2, session.workout(), 2, true)),
                    WorkoutError);
}
