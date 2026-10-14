#include "DietProfile.hpp"
#include "MenuItem.hpp"
#include "OrderError.hpp"
#include "Recipe.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("MenuItem: Позиция меню и цена порции.") {
    MenuItem value;
    CHECK(value.charge(2) == 30);
    CHECK(value.suitable(DietProfile{}));
    CHECK_THROWS_AS(value.charge(0), OrderError);
    CHECK_FALSE(MenuItem(Recipe{}, 15, false).suitable(DietProfile{}));
}
