#include "InvalidQuantityError.hpp"
#include "Quantity.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("Quantity: Масса продукта в граммах с учётом съедобной части.") {
    Quantity value(200, .8);
    CHECK(value.edible() == doctest::Approx(160));
    CHECK(value.scaled(2).grams() == 400);
    CHECK(value.combined(value).grams() == 400);
    CHECK_THROWS_AS(value.scaled(0), InvalidQuantityError);
    CHECK_THROWS_AS(value.combined(Quantity(1, 1, "мл")), InvalidQuantityError);
}
