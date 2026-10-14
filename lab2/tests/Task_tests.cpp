#include "Task.hpp"
#include "WorkflowError.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("Task: Задание повару с крайним сроком.") {
    Task value;
    CHECK(value.fits(0));
    CHECK_FALSE(value.fits(61));
    value.complete(30);
    CHECK(value.completed());
    CHECK_THROWS_AS(value.complete(30), WorkflowError);
    CHECK_THROWS_AS(Task{}.complete(100), WorkflowError);
}
