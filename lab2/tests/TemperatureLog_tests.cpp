#include "EquipmentError.hpp"
#include "TemperatureLog.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("TemperatureLog: Журнал замеров температуры оборудования.") {
    TemperatureLog value;
    CHECK_THROWS_AS(value.average(), EquipmentError);
    value.record(100);
    value.record(200);
    CHECK(value.average() == 150);
    CHECK_THROWS_AS(value.record(400), EquipmentError);
}
