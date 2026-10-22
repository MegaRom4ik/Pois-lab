#include "Nutrition.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("Nutrition: Пищевая ценность заданного количества продукта.") {
    Nutrition value(100, 5, 2, 10);
    CHECK(value.for_mass(200).calories() == 200);
    CHECK(value.combined(value).protein() == 10);
    CHECK(value.macro_energy() == 78);
}
