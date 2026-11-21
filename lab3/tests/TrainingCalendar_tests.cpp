#include "TrainingCalendar.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("TrainingCalendar: domain behavior and validation") {
    TrainingCalendar value("X", {ScheduleSlot()}, 60);
    CHECK(value.minutes_on(0) == 60);
    CHECK(value.minutes_on(1) == 0);
    CHECK_THROWS_AS(value.book(ScheduleSlot()), ScheduleError);
    CHECK_THROWS_AS(value.book(ScheduleSlot(0, 700)), ScheduleError);
    value.book(ScheduleSlot(1));
    value.cancel_day(0);
    CHECK(value.slots().size() == 1);
    CHECK_THROWS_AS(value.cancel_day(-1), ScheduleError);
    CHECK_THROWS_AS(value.minutes_on(-1), ScheduleError);
    CHECK_THROWS_AS(TrainingCalendar(""), ScheduleError);
}
