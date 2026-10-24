#include "PortionPlan.hpp"
#include "Recipe.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("PortionPlan: Расчёт порций с резервом и запасом выхода.") {
    PortionPlan value(4, 1, 1);
    CHECK(value.required() == 5);
    CHECK(value.prepare(Recipe{}).servings() == 5);
}
