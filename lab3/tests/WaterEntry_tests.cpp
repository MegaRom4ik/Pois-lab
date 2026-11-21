#include "WaterEntry.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("WaterEntry: domain behavior and validation") {
    WaterEntry value(0, 500);
    CHECK(value.liters() == .5);
    CHECK(value.cups(200) == 2);
    CHECK_THROWS_AS(value.cups(0), NutritionError);
    CHECK_THROWS_AS(WaterEntry(0, -1), NutritionError);
}
