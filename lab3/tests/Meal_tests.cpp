#include "Meal.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("Meal: domain behavior and validation") {
    Meal value;
    value.add(Food("X", Nutrients(10), 100));
    CHECK(value.total_nutrients().calories() == 40);
    CHECK(value.total_grams() == 100);
    CHECK_THROWS_AS(Meal("", -1), NutritionError);
}
