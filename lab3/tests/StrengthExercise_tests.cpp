#include "StrengthExercise.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("StrengthExercise: domain behavior and validation") {
    StrengthExercise value;
    value.add_set(ExerciseSet(10, 20));
    CHECK(value.volume() == 200);
    CHECK(value.total_repetitions() == 10);
    StrengthExercise unilateral(Exercise(), {ExerciseSet(5, 10)}, true);
    CHECK(unilateral.volume() == 100);
    CHECK(unilateral.total_repetitions() == 10);
}
