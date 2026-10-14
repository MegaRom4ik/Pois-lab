#include "EquipmentError.hpp"
#include "Quantity.hpp"
#include "Workstation.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("Workstation: Рабочее место и занятость.") {
    Workstation value;
    CHECK_THROWS_AS(value.release(), EquipmentError);
    value.reserve(Quantity{});
    CHECK(value.occupied());
    CHECK_THROWS_AS(value.reserve(Quantity{}), EquipmentError);
    value.release();
    CHECK_FALSE(value.occupied());
}
