#include "ShoppingItem.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("ShoppingItem: Позиция закупки с количеством и ценой.") {
    ShoppingItem value;
    CHECK(value.total() == 10);
    CHECK(value.increased(2).total() == 20);
}
