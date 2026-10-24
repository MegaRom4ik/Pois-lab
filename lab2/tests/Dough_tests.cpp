#include "Dough.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("Dough: Тесто: гидратация и масса.") {
    Dough value;
    CHECK(value.hydration() == 60);
    CHECK(value.total_mass().grams() == 1620);
    CHECK(value.scaled(2).total_mass().grams() == 3240);
}
