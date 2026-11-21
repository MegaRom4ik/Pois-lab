#include "Workout.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("Workout: domain behavior and validation") {
    Workout value;
    value.add_strength(StrengthExercise(Exercise(), {ExerciseSet()}));
    value.add_cardio(CardioActivity());
    CHECK(value.lifted_volume() == 200);
    CHECK(value.cardio_minutes() == 5);
    CHECK_THROWS_AS(Workout(""), WorkoutError);
}
