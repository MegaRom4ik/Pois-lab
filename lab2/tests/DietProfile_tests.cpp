#include "Allergen.hpp"
#include "DietProfile.hpp"
#include "Ingredient.hpp"
#include "IngredientAmount.hpp"
#include "Nutrition.hpp"
#include "Quantity.hpp"
#include "Recipe.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("DietProfile: Ограничения питания пользователя.") {
    DietProfile value("Гость", {Allergen("молоко")}, 100, true);
    CHECK(value.allows(Ingredient{}));
    CHECK_FALSE(value.allows(Ingredient("сыр", Nutrition{}, {"молоко"})));
    CHECK_FALSE(value.allows(Ingredient("мясо", Nutrition{}, {}, false)));
    CHECK(value.accepts(Recipe{}));
    Recipe rich;
    rich.add_ingredient(IngredientAmount(Ingredient{}, Quantity(1000)));
    CHECK_FALSE(value.accepts(rich));
    Recipe unsafe;
    unsafe.add_ingredient(IngredientAmount(Ingredient("сыр", Nutrition{}, {"молоко"})));
    CHECK_FALSE(value.accepts(unsafe));
}
