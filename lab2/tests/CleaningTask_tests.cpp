#include "CleaningTask.hpp"
#include "KitchenTool.hpp"
#include "Quantity.hpp"
#include "WorkflowError.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("CleaningTask: Мойка инструмента с учётом времени.") {
    KitchenTool tool;
    tool.use(Quantity{});
    CleaningTask value(tool);
    CHECK_THROWS_AS(value.finish(), WorkflowError);
    value.work(5);
    CHECK(value.finish().clean());
    CleaningTask clean;
    clean.work(5);
    CHECK(clean.finish().clean());
    CHECK_THROWS_AS(value.work(0), WorkflowError);
}
