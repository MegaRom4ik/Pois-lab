#include "PlatingRule.hpp"
#include "Quantity.hpp"
#include "RecipeError.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("PlatingRule: Норма подачи по массе и украшению.") {
    PlatingRule value;
    CHECK(value.for_guests(2).grams() == 520);
    CHECK(value.plates_from(Quantity(780)) == 3);
    CHECK_THROWS_AS(value.for_guests(0), RecipeError);
}
