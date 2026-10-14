#include "Fermentation.hpp"
#include "WorkflowError.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("Fermentation: Учебная оценка готовности теста по времени.") {
    Fermentation value;
    CHECK_FALSE(value.ready());
    value.advance(30);
    CHECK(value.progress() == .5);
    value.advance(40);
    CHECK(value.ready());
    CHECK(value.progress() == 1);
    CHECK_THROWS_AS(value.advance(0), WorkflowError);
}
