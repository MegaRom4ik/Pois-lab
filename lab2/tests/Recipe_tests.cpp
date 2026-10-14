#include "IngredientAmount.hpp"
#include "Recipe.hpp"
#include "RecipeError.hpp"
#include "RecipeStep.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("Recipe: Рецепт с составом и последовательностью шагов.") {
    Recipe value;
    value.add_ingredient(IngredientAmount{});
    value.add_step(RecipeStep{});
    CHECK(value.calories_per_serving() == 50);
    CHECK(value.duration() == 5);
    CHECK(value.scaled_to(4).ingredients()[0].amount().grams() == 200);
    CHECK_THROWS_AS(value.add_ingredient(IngredientAmount{}), RecipeError);
    CHECK_THROWS_AS(value.add_step(RecipeStep("Рано", 2, 9)), RecipeError);
    CHECK_THROWS_AS(value.scaled_to(0), RecipeError);
}
