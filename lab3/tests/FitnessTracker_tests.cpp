#include "FitnessTracker.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("FitnessTracker: domain behavior and validation") {
    FitnessTracker value;
    value.record_workout(WorkoutSession(1, Workout("Run", {}, {CardioActivity()}), 0, true));
    value.record_steps(StepEntry());
    value.record_weight(WeightEntry());
    value.record_water(WaterEntry());
    value.record_meal(Meal());
    value.record_sleep(SleepEntry());
    value.schedule(ScheduleSlot());
    CHECK(value.report(0, 6).find("Sessions: 1") != std::string::npos);
    CHECK(value.water().total_on(0) == 250);
    CHECK(value.food().meals().size() == 1);
    CHECK(value.sleep().entries().size() == 1);
    CHECK(value.calendar().minutes_on(0) == 60);
}
