#include "Recipe.hpp"
#include "RecipeBook.hpp"
#include "RecipeError.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("RecipeBook: Каталог рецептов с поиском и удалением.") {
    RecipeBook value;
    value.add(Recipe{});
    CHECK(value.find("Каша").servings() == 2);
    CHECK_THROWS_AS(value.add(Recipe{}), RecipeError);
    CHECK_THROWS_AS(value.find("нет"), RecipeError);
    value.remove("Каша");
    CHECK(value.recipes().empty());
    CHECK_THROWS_AS(value.remove("нет"), RecipeError);
}
