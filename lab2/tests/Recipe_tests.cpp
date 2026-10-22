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

TEST_CASE(
    "Recipe constructors validate initial ingredients and step dependencies") {
  const IngredientAmount ingredient;
  CHECK_THROWS_AS(Recipe("Duplicate", 2, {ingredient, ingredient}),
                  RecipeError);
  CHECK_THROWS_AS(
      Recipe("Invalid first step", 2, {}, {RecipeStep("Cook", 5, 99)}),
      RecipeError);
  CHECK_THROWS_AS(Recipe("Forward dependency", 2, {},
                         {RecipeStep("Mix", 2), RecipeStep("Cook", 5, 2)}),
                  RecipeError);
  const Recipe valid("Valid", 2, {ingredient},
                     {RecipeStep("Mix", 2), RecipeStep("Cook", 5, 0)});
  CHECK(valid.ingredients().size() == 1);
  CHECK(valid.steps().size() == 2);
  CHECK(valid.duration() == 7);
  const auto scaled = valid.scaled_to(4);
  CHECK(scaled.steps().size() == 2);
  CHECK(scaled.ingredients()[0].amount().grams() == 200);
}
