#include "CostEstimate.hpp"
#include "Recipe.hpp"
#include "RecipeStep.hpp"
#include "ShoppingItem.hpp"
#include "ShoppingList.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("CostEstimate: Себестоимость блюда: продукты, труд и накладные расходы.") {
    ShoppingList list;
    list.add(ShoppingItem{});
    Recipe recipe;
    recipe.add_step(RecipeStep{});
    CostEstimate value(list);
    CHECK(value.total(recipe) == 20);
    CHECK(value.per_serving(recipe) == 10);
}
