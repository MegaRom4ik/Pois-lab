#include "Feedback.hpp"
#include "Recipe.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("Feedback: Отзыв о блюде.") {
    Feedback value;
    CHECK_FALSE(value.needs_attention());
    CHECK(value.refers_to(Recipe{}));
    CHECK(Feedback("Каша", 1).needs_attention());
    CHECK_FALSE(value.refers_to(Recipe("Суп")));
}
