#include "Allergen.hpp"
#include "AllergyError.hpp"
#include "DietProfile.hpp"
#include "ExpiredFoodError.hpp"
#include "Ingredient.hpp"
#include "IngredientAmount.hpp"
#include "InventoryBatch.hpp"
#include "Kitchen.hpp"
#include "Nutrition.hpp"
#include "Recipe.hpp"
#include "RecipeBook.hpp"
#include "RecipeStep.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("Kitchen: Кулинарная мастерская: каталог, склад и готовые блюда.") {
    Kitchen value;
    Recipe recipe;
    recipe.add_ingredient(IngredientAmount{});
    recipe.add_step(RecipeStep{});
    value.register_recipe(recipe);
    value.stock(InventoryBatch{});
    CHECK(value.plan("Каша", 4, DietProfile{}).servings() == 4);
    value.cook("Каша", 2, DietProfile{});
    CHECK(value.dishes().size() == 1);
    CHECK(value.pantry().available("мука", 1) == 900);
    value.next_day();
    CHECK(value.day() == 2);
    CHECK_THROWS_AS(value.stock(InventoryBatch(Ingredient{}, 100, 0, "late")), ExpiredFoodError);
    Recipe unsafe;
    unsafe.add_ingredient(IngredientAmount(Ingredient("сыр", Nutrition{}, {"молоко"})));
    Kitchen blocked(RecipeBook("Книга", {unsafe}));
    CHECK_THROWS_AS(blocked.plan("Каша", 2, DietProfile("Гость", {Allergen{}})), AllergyError);
}
