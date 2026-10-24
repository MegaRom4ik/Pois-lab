#include "Nutrients.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("Nutrients: domain behavior and validation") {
    Nutrients value(10, 5, 20);
    CHECK(value.calories() == 165);
    CHECK(value.scaled(2).protein() == 20);
    CHECK(value.combined(value).fat() == 10);
    CHECK_THROWS_AS(value.scaled(-1), NutritionError);
    CHECK_THROWS_AS(Nutrients(-1), NutritionError);
}
