#include "HeartRateSample.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("HeartRateSample: domain behavior and validation") {
    HeartRateSample value(10, 110);
    CHECK(value.time_since(HeartRateSample()) == 10);
    CHECK(value.change_from(HeartRateSample()) == 10);
    CHECK_THROWS_AS(value.time_since(HeartRateSample(20)), SensorError);
    CHECK_THROWS_AS(HeartRateSample(0, 0), SensorError);
}
