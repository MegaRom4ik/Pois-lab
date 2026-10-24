#include "Cooking.hpp"
#include "doctest.h"
#include <limits>
using namespace cooking;
TEST_CASE("Invalid culinary states are rejected before creating an object") {
    CHECK_THROWS_AS(Chef("Повар", SkillProfile{}, -1), WorkflowError);
    CHECK_THROWS_AS(RecipeStep("Шаг", 0), RecipeError);
    CHECK_THROWS_AS(Serving(Dish{}, DietProfile{}, -1), WorkflowError);
    CHECK_THROWS_AS(Allergen("молоко", 0), IngredientError);
    CHECK_THROWS_AS(Feedback("Каша", 0), RecipeError);
    CHECK_THROWS_AS(Marinade(SeasoningBlend{}, 0), RecipeError);
    CHECK_THROWS_AS(PortionPlan(0), RecipeError);
    CHECK_THROWS_AS(ShoppingItem(IngredientAmount(Ingredient("рис"))), OrderError);
    CHECK_THROWS_AS(Task(Recipe{}, -1), WorkflowError);
    CHECK_THROWS_AS(Pantry("Полный", {InventoryBatch{}}, 1), StorageError);
    CHECK_THROWS_AS((Quantity(std::numeric_limits<double>::infinity())), InvalidQuantityError);
    CHECK_THROWS_AS(Quantity(100, 2), InvalidQuantityError);
    CHECK_THROWS_AS(Quantity(0), InvalidQuantityError);
    CHECK_THROWS_AS(Ingredient("   "), IngredientError);
    CHECK_THROWS_AS(Nutrition(-1), InvalidQuantityError);
}
