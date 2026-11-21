#include "Food.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("Food: domain behavior and validation") {
    Food value("Oats", Nutrients(10, 5, 60), 50);
    CHECK(value.portion_nutrients().protein() == 5);
    CHECK(value.resized(200).portion_nutrients().protein() == 20);
    CHECK_THROWS_AS(Food(""), NutritionError);
    CHECK_THROWS_AS(value.resized(0), NutritionError);
}
