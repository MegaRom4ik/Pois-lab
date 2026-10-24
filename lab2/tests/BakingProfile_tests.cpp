#include "BakingProfile.hpp"
#include "Oven.hpp"
#include "WorkflowError.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("BakingProfile: Режим выпечки и проверка духовки.") {
    BakingProfile value;
    Oven oven;
    value.prepare(oven);
    CHECK(oven.ready_for(180));
    CHECK(value.finish_at(10) == 40);
    CHECK_THROWS_AS(value.finish_at(-1), WorkflowError);
}
