#include "SleepEntry.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("SleepEntry: domain behavior and validation") {
    SleepEntry value;
    CHECK(value.minutes() == 480);
    CHECK(value.hours_per_interruption() == 8);
    CHECK(SleepEntry(0, 100, 220, 1).hours_per_interruption() == 1);
    CHECK_THROWS_AS(SleepEntry(0, 0, 0), RecoveryError);
}
