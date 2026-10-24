#include "ScheduleSlot.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("ScheduleSlot: domain behavior and validation") {
    ScheduleSlot value;
    CHECK(value.end_minute() == 660);
    CHECK(value.overlaps(ScheduleSlot(0, 630)));
    CHECK_FALSE(value.overlaps(ScheduleSlot(1, 630)));
    CHECK_FALSE(value.overlaps(ScheduleSlot(0, 660)));
    CHECK_THROWS_AS(ScheduleSlot(0, 1400, 60), ScheduleError);
}
