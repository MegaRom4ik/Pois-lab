#include "PersonalRecord.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("PersonalRecord: domain behavior and validation") {
    PersonalRecord value(Exercise(), 30);
    CHECK(value.beats(PersonalRecord()));
    CHECK(value.improvement(PersonalRecord()) == 10);
    CHECK_FALSE(PersonalRecord().beats(value));
    CHECK_THROWS_AS(value.beats(PersonalRecord(Exercise("Press"))), GoalError);
    CHECK_THROWS_AS(value.improvement(PersonalRecord(Exercise(), 10, 5)), GoalError);
    CHECK_THROWS_AS(PersonalRecord(Exercise(), -1), GoalError);
}
