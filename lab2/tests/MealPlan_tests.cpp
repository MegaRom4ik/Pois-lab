#include "Allergen.hpp"
#include "AllergyError.hpp"
#include "DietProfile.hpp"
#include "Ingredient.hpp"
#include "IngredientAmount.hpp"
#include "MealPlan.hpp"
#include "Nutrition.hpp"
#include "Recipe.hpp"
#include "RecipeError.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("MealPlan: План питания с суммированием калорий.") {
    Recipe recipe;
    recipe.add_ingredient(IngredientAmount{});
    MealPlan value(DietProfile{}, {}, 50);
    value.add(recipe);
    CHECK(value.calories() == 50);
    CHECK_THROWS_AS(value.add(recipe), RecipeError);
    Recipe unsafe;
    unsafe.add_ingredient(IngredientAmount(Ingredient("сыр", Nutrition{}, {"молоко"})));
    CHECK_THROWS_AS(MealPlan(DietProfile("Гость", {Allergen{}})).add(unsafe), AllergyError);
}
