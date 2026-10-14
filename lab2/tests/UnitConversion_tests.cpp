#include "Ingredient.hpp"
#include "Quantity.hpp"
#include "UnitConversion.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("UnitConversion: Перевод массы в объём по плотности.") {
    UnitConversion value(Ingredient{}, .5);
    CHECK(value.volume_for(Quantity(100)) == 200);
    CHECK(value.mass_for(200).grams() == 100);
}
