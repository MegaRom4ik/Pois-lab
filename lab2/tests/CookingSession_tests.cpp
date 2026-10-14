#include "CookingSession.hpp"
#include "IngredientAmount.hpp"
#include "InventoryBatch.hpp"
#include "Pantry.hpp"
#include "Recipe.hpp"
#include "RecipeStep.hpp"
#include "WorkflowError.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("CookingSession: Приготовление по шагам с безопасным расходом склада.") {
    Recipe recipe;
    recipe.add_ingredient(IngredientAmount{});
    recipe.add_step(RecipeStep{});
    Pantry pantry;
    pantry.receive(InventoryBatch{});
    CookingSession value(recipe);
    CHECK_THROWS_AS(value.complete_step(), WorkflowError);
    CHECK_THROWS_AS(value.finish(), WorkflowError);
    CHECK_THROWS_AS(CookingSession{}.begin(pantry), WorkflowError);
    value.begin(pantry);
    CHECK(pantry.available("мука", 1) == 900);
    CHECK_THROWS_AS(value.begin(pantry), WorkflowError);
    CHECK_THROWS_AS(value.finish(), WorkflowError);
    value.complete_step();
    CHECK(value.finish().remaining() == 2);
    CHECK_THROWS_AS(value.complete_step(), WorkflowError);
}
