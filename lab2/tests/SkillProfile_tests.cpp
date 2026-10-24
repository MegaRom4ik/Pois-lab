#include "SkillProfile.hpp"
#include "WorkflowError.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("SkillProfile: Квалификация повара по техникам.") {
    SkillProfile value;
    CHECK(value.qualifies("выпечка", 1));
    CHECK_FALSE(value.qualifies("суп", 1));
    value.practice(20);
    CHECK(value.level() == 3);
    CHECK_THROWS_AS(value.practice(0), WorkflowError);
}
