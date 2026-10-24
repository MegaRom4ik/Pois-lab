#include "Duration.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("Duration: domain behavior and validation") {
    Duration value(120, 30, 90);
    CHECK(value.elapsed() == 240);
    CHECK(value.active_minutes() == 2);
    CHECK(value.active_share() == .5);
    CHECK(Duration(0).active_share() == 0);
    CHECK_THROWS_AS(Duration(-1), DurationError);
}
