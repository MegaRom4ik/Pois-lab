#include "Dish.hpp"
#include "IngredientAmount.hpp"
#include "Recipe.hpp"
#include "WorkflowError.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("Dish: Готовое блюдо с количеством оставшихся порций.") {
    Recipe recipe;
    recipe.add_ingredient(IngredientAmount{});
    Dish value(recipe);
    CHECK(value.calories_for(2) == 100);
    value.serve(1);
    CHECK(value.remaining() == 1);
    CHECK_THROWS_AS(value.serve(2), WorkflowError);
    CHECK_THROWS_AS(value.calories_for(0), WorkflowError);
}
