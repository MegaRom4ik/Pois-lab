#include "Participant.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("Participant: domain behavior and validation") {
    WorkoutSession session(1, Workout("X", {}, {CardioActivity()}), 1, true);
    Participant value("Roman", StepHistory({StepEntry(0), StepEntry(1, 0), StepEntry(3)}),
                      WorkoutLog({session}));
    CHECK(value.step_score(0, 1) == 1000);
    CHECK(value.active_days(0, 1) == 2);
    CHECK_THROWS_AS(value.active_days(2, 1), GoalError);
    CHECK_THROWS_AS(Participant(""), GoalError);
}
