#include "WalkingRoute.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("WalkingRoute: domain behavior and validation") {
    WalkingRoute value;
    value.extend(Distance(500, 20));
    CHECK(value.total_distance().ascent() == 20);
    CHECK(value.round_trip_meters() == 1000);
    CHECK(WalkingRoute("Loop", {Distance(500)}, true).round_trip_meters() == 500);
    CHECK_THROWS_AS(WalkingRoute(""), DistanceError);
}
