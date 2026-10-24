#include "Assignment.hpp"
#include "WorkflowError.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("Assignment: Назначение задания повару и месту.") {
    Assignment value;
    CHECK_THROWS_AS(value.finish(1), WorkflowError);
    value.start(0);
    CHECK(value.started());
    CHECK_THROWS_AS(value.start(0), WorkflowError);
    value.finish(20);
    CHECK(value.task().completed());
}
