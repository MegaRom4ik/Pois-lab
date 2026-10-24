#include "Lap.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("Lap: domain behavior and validation") {
    Lap value;
    CHECK(value.seconds_per_100m() == 30);
    CHECK(value.time_difference(Lap(2, Distance(), Duration(310))) == -10);
    CHECK_THROWS_AS(value.time_difference(Lap(2, Distance(500))), DistanceError);
    CHECK_THROWS_AS(Lap(0), DistanceError);
}
