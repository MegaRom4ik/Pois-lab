#include "Quantity.hpp"
#include "SeasoningBlend.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("SeasoningBlend: Смесь приправ с нормой дозировки.") {
    SeasoningBlend value;
    CHECK(value.dose(Quantity(2000)).grams() == 10);
    CHECK(value.component_share("мука") == 1);
    CHECK(value.component_share("нет") == 0);
    CHECK(SeasoningBlend("Пусто", {}).component_share("нет") == 0);
}
