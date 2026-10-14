#include "EquipmentError.hpp"
#include "Oven.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("Oven: Духовка: нагрев, проверка режима и остывание.") {
    Oven value;
    CHECK_FALSE(value.ready_for(180));
    value.preheat(180);
    CHECK(value.ready_for(170));
    CHECK_THROWS_AS(value.preheat(400), EquipmentError);
    CHECK_THROWS_AS(value.cool(200), EquipmentError);
    value.cool(20);
    CHECK_FALSE(value.powered());
}
