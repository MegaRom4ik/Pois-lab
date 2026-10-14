#include "Marinade.hpp"
#include "Quantity.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("Marinade: План маринования по массе и времени.") {
    Marinade value;
    CHECK(value.duration(Quantity(1500)) == 90);
    CHECK(value.liquid_for(Quantity(1000)).grams() == 200);
}
