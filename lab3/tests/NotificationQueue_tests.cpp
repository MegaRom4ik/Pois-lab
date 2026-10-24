#include "NotificationQueue.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("NotificationQueue: domain behavior and validation") {
    NotificationQueue value;
    value.enqueue(Reminder());
    CHECK(value.deliver(0, 500).empty());
    CHECK(value.deliver(0, 600) == std::vector<std::string>{"Workout"});
    CHECK(value.deliver(1, 0).empty());
    CHECK_THROWS_AS(value.deliver(0, -1), ScheduleError);
    CHECK_THROWS_AS(NotificationQueue(""), ScheduleError);
    CHECK_THROWS_AS(NotificationQueue("X", {Reminder()}, 1).enqueue(Reminder()), ScheduleError);
}
