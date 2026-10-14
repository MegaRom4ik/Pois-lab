#include "Recipe.hpp"
#include "RecipeStep.hpp"
#include "Schedule.hpp"
#include "Task.hpp"
#include "WorkflowError.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("Schedule: План заданий с проверкой общего времени.") {
    Recipe recipe;
    recipe.add_step(RecipeStep{});
    Schedule value("День", {}, 5);
    value.add(Task(recipe));
    CHECK(value.workload() == 5);
    CHECK_THROWS_AS(value.add(Task(recipe)), WorkflowError);
}
