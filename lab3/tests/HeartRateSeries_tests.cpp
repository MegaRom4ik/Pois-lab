#include "HeartRateSeries.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("HeartRateSeries: domain behavior and validation") {
    HeartRateSeries value({HeartRateSample(0, 120), HeartRateSample(30, 90), HeartRateSample(100, 110)});
    CHECK(value.average() == doctest::Approx(320.0 / 3));
    CHECK(value.seconds_in(HeartRateZone()) == 30);
    value.append(HeartRateSample(110, 100));
    CHECK(value.seconds_in(HeartRateZone()) == 40);
    CHECK_THROWS_AS(value.append(HeartRateSample(110)), SensorError);
    CHECK_THROWS_AS(HeartRateSeries().average(), SensorError);
    CHECK_THROWS_AS(HeartRateSeries({}, "", 0), SensorError);
}
