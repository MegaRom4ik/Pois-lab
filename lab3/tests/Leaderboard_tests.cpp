#include "Leaderboard.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("Leaderboard: domain behavior and validation") {
    Leaderboard value(
        "X", {Participant("Bob"), Participant("Amy"), Participant("Roman", StepHistory({StepEntry()}))});
    CHECK(value.ranking(6) == std::vector<std::string>{"Roman", "Amy", "Bob"});
    CHECK_THROWS_AS(value.join(Participant("Bob")), GoalError);
    CHECK_THROWS_AS(value.ranking(-1), GoalError);
    CHECK_THROWS_AS(Leaderboard(""), GoalError);
}
