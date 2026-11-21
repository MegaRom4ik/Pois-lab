#include "CardioActivity.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("CardioActivity: domain behavior and validation") {
    CardioActivity value("Run", Distance(2000), Duration(600));
    CHECK(value.speed_kmh() == 12);
    CHECK(value.pace_minutes() == 5);
    CHECK_THROWS_AS(CardioActivity("", Distance()), WorkoutError);
    CHECK_THROWS_AS(CardioActivity("Run", Distance(), Duration(0)), WorkoutError);
    CHECK_THROWS_AS(CardioActivity("Run", Distance(0)).pace_minutes(), WorkoutError);
}
