#include "Ingredient.hpp"
#include "IngredientAmount.hpp"
#include "InventoryBatch.hpp"
#include "Pantry.hpp"
#include "Quantity.hpp"
#include "Recipe.hpp"
#include "StockError.hpp"
#include "StorageError.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("Pantry: Склад: расходует сначала партии с ближайшим сроком.") {
    Pantry value;
    value.receive(InventoryBatch{});
    CHECK(value.stored() == 1000);
    CHECK(value.available("мука", 1) == 1000);
    CHECK(value.available("мука", 31) == 0);
    CHECK_THROWS_AS(value.receive(InventoryBatch{}), StockError);
    CHECK_THROWS_AS(Pantry("Малый", {}, 1).receive(InventoryBatch{}), StorageError);
    Recipe recipe;
    recipe.add_ingredient(IngredientAmount{});
    recipe.add_ingredient(IngredientAmount(Ingredient("вода"), Quantity(10), true));
    value.consume_recipe(recipe, 1);
    CHECK(value.available("мука", 1) == 900);
    CHECK_THROWS_AS(value.consume("мука", 1000, 1), StockError);
    Recipe missing;
    missing.add_ingredient(IngredientAmount{});
    missing.add_ingredient(IngredientAmount(Ingredient("рис")));
    CHECK_THROWS_AS(value.consume_recipe(missing, 1), StockError);
    CHECK(value.available("мука", 1) == 900);
    value.receive(InventoryBatch(Ingredient("рис"), 50, 20, "B1"));
    value.receive(InventoryBatch(Ingredient{}, 100, 10, "A2"));
    value.consume("мука", 950, 1);
    CHECK(value.available("мука", 1) == 50);
}
