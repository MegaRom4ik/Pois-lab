#include "BodyMeasurement.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("BodyMeasurement: domain behavior and validation") {
    BodyMeasurement value(2, 78, 100);
    CHECK(value.waist_change(BodyMeasurement(1, 80)) == -2);
    CHECK(value.chest_waist_difference() == 22);
    CHECK_THROWS_AS(value.waist_change(BodyMeasurement(3)), MeasurementError);
    CHECK_THROWS_AS(BodyMeasurement(-1), MeasurementError);
}
