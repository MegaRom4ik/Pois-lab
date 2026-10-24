#include "IntervalPlan.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("IntervalPlan: domain behavior and validation") {
    IntervalPlan value;
    value.append(Interval());
    CHECK(value.elapsed_minutes() == 11);
    CHECK(value.work_fraction() == doctest::Approx(540.0 / 660));
    CHECK(IntervalPlan("Empty", Duration(0)).work_fraction() == 0);
    CHECK_THROWS_AS(IntervalPlan(""), PlanError);
}
