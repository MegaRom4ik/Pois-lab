#include "IngredientAmount.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("IngredientAmount: Строка рецепта: продукт, количество и обязательность.") {
    IngredientAmount value;
    CHECK(value.calories() == 100);
    CHECK(value.scaled(2).amount().grams() == 200);
}
