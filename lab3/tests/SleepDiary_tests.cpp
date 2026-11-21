#include "SleepDiary.hpp"
#include "doctest.h"
#include <type_traits>
using namespace fitness;
TEST_CASE("SleepDiary: domain behavior and validation") {
    SleepDiary value({SleepEntry(), SleepEntry(1, 0, 360)});
    CHECK(value.average_hours() == 7);
    CHECK(value.total_deficit() == 120);
    CHECK(SleepDiary().average_hours() == 0);
    CHECK_THROWS_AS(value.record(SleepEntry()), RecoveryError);
    CHECK_THROWS_AS(SleepDiary({}, 0), RecoveryError);
}

TEST_CASE("SleepDiary bounds the daily target and uses a wide deficit total") {
    CHECK_THROWS_AS(SleepDiary({}, std::numeric_limits<int>::max()), RecoveryError);
    CHECK_THROWS_AS(SleepDiary({}, minutes_per_day + 1), RecoveryError);
    CHECK(SleepDiary({}, 1).target_minutes() == 1);
    const SleepDiary diary({SleepEntry(0), SleepEntry(1)}, minutes_per_day);
    static_assert(std::is_same_v<decltype(diary.total_deficit()), long long>);
    CHECK(diary.total_deficit() == 1920LL);
    CHECK(SleepDiary({SleepEntry(0)}, 1).total_deficit() == 0);
}
