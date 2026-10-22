#include "OrderError.hpp"
#include "ShoppingItem.hpp"
#include "ShoppingList.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("ShoppingList: Список покупок с ограничением числа позиций.") {
    ShoppingList value("Список", {}, 1);
    value.add(ShoppingItem{});
    CHECK(value.total() == 10);
    CHECK_THROWS_AS(value.add(ShoppingItem{}), OrderError);
    value.remove_product("мука");
    CHECK(value.total() == 0);
    CHECK_THROWS_AS(value.remove_product("нет"), OrderError);
}
