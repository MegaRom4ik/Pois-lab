#include "Allergen.hpp"
#include "Ingredient.hpp"
#include "Nutrition.hpp"
#include "Quantity.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("Ingredient: Продукт, пищевая ценность и аллергены.") {
    Ingredient value("мука", Nutrition(100), {"глютен"});
    CHECK(value.nutrition_for(Quantity(200)).calories() == 200);
    CHECK(value.contains(Allergen("глютен")));
    CHECK_FALSE(value.contains(Allergen("молоко")));
}
