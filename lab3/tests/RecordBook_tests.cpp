#include "RecordBook.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("RecordBook: domain behavior and validation") {
    RecordBook value({PersonalRecord()});
    CHECK(value.best_load("Squat", 10) == 20);
    CHECK_FALSE(value.submit(PersonalRecord()));
    CHECK(value.submit(PersonalRecord(Exercise(), 30)));
    CHECK(value.submit(PersonalRecord(Exercise("Press"))));
    CHECK(value.submit(PersonalRecord(Exercise(), 5, 2)));
    CHECK(value.best_load("Squat", 10) == 30);
    CHECK_THROWS_AS(value.best_load("Missing", 10), GoalError);
    CHECK_THROWS_AS(RecordBook({}, "", 0), GoalError);
    CHECK_THROWS_AS(RecordBook({PersonalRecord()}, "X", 1).submit(PersonalRecord(Exercise("Press"))),
                    GoalError);
}
