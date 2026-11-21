#include "FoodDiary.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("FoodDiary: domain behavior and validation") {
    FoodDiary value;
    value.record(Meal("Breakfast", 0, {Food("X", Nutrients(10))}));
    CHECK(value.calories_on(0) == 40);
    CHECK(value.calories_on(1) == 0);
    CHECK(value.budget_balance(0) == 1960);
    CHECK_THROWS_AS(value.calories_on(-1), NutritionError);
    CHECK_THROWS_AS(FoodDiary({}, 0), NutritionError);
}
