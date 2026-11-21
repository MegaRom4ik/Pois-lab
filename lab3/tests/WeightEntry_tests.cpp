#include "WeightEntry.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("WeightEntry: domain behavior and validation") {
    WeightEntry value(2, 72);
    CHECK(value.change_from(WeightEntry(1, 70)) == 2);
    CHECK(value.within(72, 0));
    CHECK_FALSE(value.within(70, 1));
    CHECK_THROWS_AS(value.within(-1, 0), MeasurementError);
    CHECK_THROWS_AS(value.change_from(WeightEntry(3)), MeasurementError);
    CHECK_THROWS_AS(WeightEntry(0, 0), MeasurementError);
}
