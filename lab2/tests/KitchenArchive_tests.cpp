#include "KitchenArchive.hpp"
#include "doctest.h"
#include <sstream>
using namespace cooking;
TEST_CASE("Archive restores recipes, nutritional values and pantry") {
    Kitchen kitchen;
    Recipe recipe("Овсяная каша", 3);
    recipe.add_ingredient(
        IngredientAmount(Ingredient("Овёс", Nutrition(340, 12, 5, 60), {"глютен"}), Quantity(150, .9)));
    recipe.add_step(RecipeStep("Варить 10 минут", 10));
    kitchen.register_recipe(recipe);
    kitchen.stock(InventoryBatch(Ingredient("Овёс"), 800, 10, "Партия 1"));
    std::stringstream stream;
    KitchenArchive archive;
    archive.save(kitchen, stream);
    const auto restored = archive.load(stream);
    CHECK(restored.book().find("Овсяная каша").duration() == 10);
    CHECK(restored.book().find("Овсяная каша").ingredients()[0].ingredient().nutrition().protein() == 12);
    CHECK(restored.pantry().available("Овёс", 1) == 800);
    CHECK(restored.pantry().batches()[0].lot() == "Партия 1");
}
TEST_CASE("Archive rejects malformed or incompatible data") {
    KitchenArchive archive;
    for (const auto *value :
         {"", "OTHER 1", "COOKING 2", "COOKING 1 1 \"Книга\" -1", "COOKING 1 1 \"Книга\" 1001",
          "COOKING 1 1 \"Книга\" 0 \"Склад\" -1 0", "COOKING 1 1 \"Книга\" 0 \"Склад\" 100 0 garbage"}) {
        std::istringstream stream(value);
        CHECK_THROWS_AS(archive.load(stream), SerializationError);
    }
    CHECK_THROWS_AS(KitchenArchive(2), SerializationError);
    std::ostringstream failed;
    failed.setstate(std::ios::badbit);
    CHECK_THROWS_AS(archive.save(Kitchen{}, failed), SerializationError);
}
