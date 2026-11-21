#include "WeightHistory.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("WeightHistory: domain behavior and validation") {
    WeightHistory value({}, 69, 0);
    CHECK_FALSE(value.goal_reached());
    CHECK_THROWS_AS(value.total_change(), MeasurementError);
    value.add(WeightEntry(1, 70));
    value.add(WeightEntry(2, 69));
    CHECK(value.total_change() == -1);
    CHECK(value.goal_reached());
    CHECK_THROWS_AS(value.add(WeightEntry(2)), MeasurementError);
    CHECK_THROWS_AS(WeightHistory({}, -1), MeasurementError);
    CHECK(WeightHistory({WeightEntry(0)}).entries().size() == 1);
}
