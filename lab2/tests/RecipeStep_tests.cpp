#include "RecipeStep.hpp"
#include "WorkflowError.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("RecipeStep: Шаг приготовления с длительностью и зависимостью.") {
    RecipeStep value("Смешать", 5, 0);
    CHECK_FALSE(value.ready(0));
    CHECK(value.ready(1));
    CHECK(value.finish_at(10) == 15);
    CHECK_THROWS_AS(value.finish_at(-1), WorkflowError);
}
