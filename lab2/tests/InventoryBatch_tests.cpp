#include "ExpiredFoodError.hpp"
#include "InventoryBatch.hpp"
#include "StockError.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("InventoryBatch: Партия продукта со сроком годности.") {
    InventoryBatch value;
    CHECK(value.usable(1));
    CHECK_FALSE(value.usable(31));
    value.consume(100, 1);
    CHECK(value.grams() == 900);
    CHECK_THROWS_AS(value.consume(1000, 1), StockError);
    CHECK_THROWS_AS(value.consume(1, 31), ExpiredFoodError);
}
