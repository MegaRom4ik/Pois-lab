#include "HydrationLog.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("HydrationLog: domain behavior and validation") {
    HydrationLog value;
    value.drink(WaterEntry());
    CHECK(value.total_on(0) == 250);
    CHECK(value.total_on(1) == 0);
    CHECK(value.remaining_on(0) == 1750);
    CHECK(HydrationLog({WaterEntry(0, 3000)}).remaining_on(0) == 0);
    CHECK_THROWS_AS(value.total_on(-1), NutritionError);
    CHECK_THROWS_AS(HydrationLog({}, 0), NutritionError);
}
