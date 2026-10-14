#include "Timer.hpp"
#include "WorkflowError.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("Timer: Таймер шага приготовления.") {
    Timer value;
    CHECK_THROWS_AS(value.tick(1), WorkflowError);
    value.start();
    CHECK_THROWS_AS(value.start(), WorkflowError);
    value.tick(2);
    CHECK(value.remaining() == 3);
    value.tick(10);
    CHECK(value.elapsed() == 5);
    CHECK_FALSE(value.running());
    CHECK_THROWS_AS(value.start(), WorkflowError);
}
