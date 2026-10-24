#include "ProgressReport.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("ProgressReport: domain behavior and validation") {
    ProgressReport value({}, StepHistory({StepEntry()}), WeightHistory({WeightEntry(0), WeightEntry(1, 69)}));
    CHECK(value.render(0, 6).find("Steps: 1000") != std::string::npos);
    CHECK(value.render(0, 6).find("Weight change (all records): -1") != std::string::npos);
    CHECK(ProgressReport().render(0, 6).find("Weight") == std::string::npos);
    CHECK(value.sessions_per_week(0, 6) == 0);
    CHECK_THROWS_AS(value.sessions_per_week(2, 1), GoalError);
}
