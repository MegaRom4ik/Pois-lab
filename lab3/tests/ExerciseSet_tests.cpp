#include "ExerciseSet.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("ExerciseSet: domain behavior and validation") {
    ExerciseSet value(10, 20, 60);
    CHECK(value.volume() == 200);
    CHECK(value.deloaded(.5).load_kg() == 10);
    CHECK_THROWS_AS(value.deloaded(0), ExerciseError);
    CHECK_THROWS_AS(ExerciseSet(0), ExerciseError);
}
