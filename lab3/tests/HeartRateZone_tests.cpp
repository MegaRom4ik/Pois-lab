#include "HeartRateZone.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("HeartRateZone: domain behavior and validation") {
    HeartRateZone value;
    CHECK(value.contains(HeartRateSample(0, 120)));
    CHECK_FALSE(value.contains(HeartRateSample(0, 90)));
    CHECK(value.overlap_width(HeartRateZone("X", 130, 150)) == 11);
    CHECK(value.overlap_width(HeartRateZone("X", 150, 160)) == 0);
    CHECK_THROWS_AS(HeartRateZone("X", 140, 100), SensorError);
}
