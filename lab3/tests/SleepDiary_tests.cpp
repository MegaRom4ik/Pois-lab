#include "SleepDiary.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("SleepDiary: domain behavior and validation") {
    SleepDiary value({SleepEntry(), SleepEntry(1, 0, 360)});
    CHECK(value.average_hours() == 7);
    CHECK(value.total_deficit() == 120);
    CHECK(SleepDiary().average_hours() == 0);
    CHECK_THROWS_AS(value.record(SleepEntry()), RecoveryError);
    CHECK_THROWS_AS(SleepDiary({}, 0), RecoveryError);
}
