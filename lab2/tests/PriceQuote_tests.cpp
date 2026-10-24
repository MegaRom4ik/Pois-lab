#include "OrderError.hpp"
#include "PriceQuote.hpp"
#include "Quantity.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("PriceQuote: Предложение цены за килограмм продукта.") {
    PriceQuote value;
    CHECK(value.cost(Quantity(500), 1) == 50);
    CHECK(value.cheaper_than(PriceQuote("мука", 200)));
    CHECK_THROWS_AS(value.cost(Quantity{}, 31), OrderError);
    CHECK_THROWS_AS(value.cheaper_than(PriceQuote("рис")), OrderError);
}
