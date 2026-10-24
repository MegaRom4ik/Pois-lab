#include "EquipmentError.hpp"
#include "KitchenTool.hpp"
#include "Quantity.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("KitchenTool: Инструмент с вместимостью и обязательной мойкой.") {
    KitchenTool value;
    value.use(Quantity{});
    CHECK_FALSE(value.clean());
    CHECK_THROWS_AS(value.use(Quantity{}), EquipmentError);
    value.wash();
    CHECK(value.clean());
    CHECK_THROWS_AS(value.wash(), EquipmentError);
    CHECK_THROWS_AS(value.use(Quantity(3000)), EquipmentError);
}
