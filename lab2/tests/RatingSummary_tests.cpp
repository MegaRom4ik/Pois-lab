#include "Feedback.hpp"
#include "RatingSummary.hpp"
#include "RecipeError.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("RatingSummary: Средняя оценка конкретного рецепта.") {
    RatingSummary value;
    CHECK_THROWS_AS(value.average(), RecipeError);
    value.add(Feedback{});
    value.add(Feedback("Каша", 3));
    CHECK(value.average() == 4);
    CHECK_THROWS_AS(value.add(Feedback("Суп")), RecipeError);
}
