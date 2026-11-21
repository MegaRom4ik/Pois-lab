#include "Equipment.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("Equipment: domain behavior and validation") {
    Equipment value;
    CHECK_THROWS_AS(value.reserve(201), EquipmentError);
    value.reserve(100);
    CHECK_FALSE(value.available());
    CHECK_THROWS_AS(value.reserve(1), EquipmentError);
    value.release();
    CHECK(value.available());
    CHECK_THROWS_AS(value.release(), EquipmentError);
    CHECK_THROWS_AS(Equipment(""), EquipmentError);
}
