#include "Interval.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("Interval: domain behavior and validation") {
    Interval value;
    CHECK(value.total_seconds() == 360);
    CHECK(value.work_seconds() == 240);
    CHECK_THROWS_AS(Interval(Duration(0)), PlanError);
}
