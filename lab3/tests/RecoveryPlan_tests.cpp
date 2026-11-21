#include "RecoveryPlan.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("RecoveryPlan: domain behavior and validation") {
    RecoveryPlan value;
    CHECK(value.rest_days({}) == 7);
    CHECK(value.respected({}));
    TrainingCalendar calendar("X", {ScheduleSlot(0)});
    CHECK(RecoveryPlan("X", 7).rest_days(calendar) == 6);
    CHECK_FALSE(RecoveryPlan("X", 7).respected(calendar));
    CHECK_THROWS_AS(RecoveryPlan("X", 8), RecoveryError);
}
