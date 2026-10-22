#include "Allergen.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("Allergen: Аллерген и порог чувствительности.") {
    Allergen value;
    CHECK(value.matches("молоко"));
    CHECK_FALSE(value.matches("орех"));
    CHECK(value.blocks(3, false));
    CHECK_FALSE(value.blocks(1, false));
    CHECK_FALSE(Allergen("молоко", 2, false).blocks(3, true));
}
