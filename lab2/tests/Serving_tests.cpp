#include "Allergen.hpp"
#include "AllergyError.hpp"
#include "DietProfile.hpp"
#include "Dish.hpp"
#include "Ingredient.hpp"
#include "IngredientAmount.hpp"
#include "Nutrition.hpp"
#include "Recipe.hpp"
#include "Serving.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("Serving: Выдача блюда гостю с проверкой диеты.") {
    Recipe recipe;
    recipe.add_ingredient(IngredientAmount{});
    Serving value{Dish(recipe)};
    value.deliver(1);
    CHECK(value.delivered_calories() == 50);
    Recipe unsafe;
    unsafe.add_ingredient(IngredientAmount(Ingredient("сыр", Nutrition{}, {"молоко"})));
    Serving blocked(Dish(unsafe), DietProfile("Гость", {Allergen{}}));
    CHECK_THROWS_AS(blocked.deliver(1), AllergyError);
}
