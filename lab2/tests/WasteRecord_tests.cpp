#include "OrderError.hpp"
#include "PriceQuote.hpp"
#include "Quantity.hpp"
#include "WasteRecord.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("WasteRecord: Учёт списания продукта и стоимости потерь.") {
    WasteRecord value;
    CHECK(value.loss(PriceQuote{}, 1) == 10);
    CHECK(value.fraction_of(Quantity(1000)) == doctest::Approx(.1));
    CHECK_THROWS_AS(value.loss(PriceQuote("рис"), 1), OrderError);
}
