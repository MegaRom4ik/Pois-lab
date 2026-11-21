#include "Exercise.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("Exercise: domain behavior and validation") {
    Exercise value("Press", "chest", "barbell");
    CHECK(value.trains("chest"));
    CHECK_FALSE(value.trains("legs"));
    CHECK(value.possible_with({"barbell"}));
    CHECK_FALSE(value.possible_with({}));
    CHECK(Exercise().possible_with({}));
    CHECK_THROWS_AS(Exercise(""), ExerciseError);
}
