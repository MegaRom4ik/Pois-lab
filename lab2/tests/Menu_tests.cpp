#include "DietProfile.hpp"
#include "Menu.hpp"
#include "MenuItem.hpp"
#include "OrderError.hpp"
#include "Recipe.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("Menu: Меню с подбором по рациону.") {
    Menu value("Обед", {}, 1);
    value.add(MenuItem{});
    CHECK(value.select(DietProfile{}).size() == 1);
    CHECK_THROWS_AS(value.add(MenuItem{}), OrderError);
    CHECK(Menu("Нет", {MenuItem(Recipe{}, 15, false)}).select(DietProfile{}).empty());
}
