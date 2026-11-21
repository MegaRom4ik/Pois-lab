#include "Reminder.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("Reminder: domain behavior and validation") {
    Reminder value;
    CHECK_FALSE(value.due(0, 500));
    CHECK(value.due(0, 600));
    CHECK(value.due(1, 0));
    value.postpone(2);
    CHECK_FALSE(value.due(1, 700));
    value.dismiss();
    CHECK_FALSE(value.due(3, 0));
    CHECK_THROWS_AS(value.postpone(0), ScheduleError);
    CHECK_THROWS_AS(value.due(-1, 0), ScheduleError);
    CHECK_THROWS_AS(Reminder(""), ScheduleError);
}
