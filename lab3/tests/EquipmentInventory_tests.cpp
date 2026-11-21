#include "EquipmentInventory.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("EquipmentInventory: domain behavior and validation") {
    EquipmentInventory value("X", {Equipment("Bike"), Equipment()});
    value.reserve("Barbell", 20);
    CHECK_FALSE(value.items()[1].available());
    value.release("Barbell");
    CHECK(value.items()[1].available());
    CHECK_THROWS_AS(value.reserve("Missing", 0), EquipmentError);
    CHECK_THROWS_AS(value.release("Missing"), EquipmentError);
    CHECK_THROWS_AS(value.add(Equipment()), EquipmentError);
    CHECK_THROWS_AS(EquipmentInventory("X", {Equipment()}, 1).add(Equipment("Bike")), EquipmentError);
    CHECK_THROWS_AS(EquipmentInventory(""), EquipmentError);
}
