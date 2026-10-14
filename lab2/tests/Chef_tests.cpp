#include "Chef.hpp"
#include "Recipe.hpp"
#include "RecipeStep.hpp"
#include "SkillProfile.hpp"
#include "WorkflowError.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("Chef: Повар с навыками и доступным рабочим временем.") {
    Chef value;
    Recipe recipe;
    recipe.add_step(RecipeStep{});
    value.assign(recipe);
    CHECK(value.available_minutes() == 475);
    CHECK(value.can_cook("выпечка", 1));
    CHECK_THROWS_AS(Chef("Повар", SkillProfile{}, 1).assign(recipe), WorkflowError);
}
