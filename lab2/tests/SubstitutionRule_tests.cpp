#include "DietProfile.hpp"
#include "Ingredient.hpp"
#include "IngredientAmount.hpp"
#include "IngredientError.hpp"
#include "SubstitutionRule.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("SubstitutionRule: Замена продукта с коэффициентом массы.") {
    SubstitutionRule value;
    CHECK(value.apply(IngredientAmount(Ingredient("молоко"))).ingredient().name() == "вода");
    CHECK(value.compatible(DietProfile{}));
    CHECK_THROWS_AS(value.apply(IngredientAmount{}), IngredientError);
}
