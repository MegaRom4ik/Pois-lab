#include "Ingredient.hpp"
#include "IngredientAmount.hpp"
#include "OrderError.hpp"
#include "PriceQuote.hpp"
#include "ShoppingItem.hpp"
#include "ShoppingList.hpp"
#include "Supplier.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("Supplier: Поставщик с ассортиментом и минимальной суммой заказа.") {
    Supplier value;
    CHECK(value.quote_for("мука").per_kg() == 100);
    CHECK_THROWS_AS(value.quote_for("нет"), OrderError);
    ShoppingList list;
    CHECK_FALSE(value.accepts(list));
    list.add(ShoppingItem{});
    CHECK(value.accepts(list));
    ShoppingList unknown;
    unknown.add(ShoppingItem(IngredientAmount(Ingredient("рис")), PriceQuote("рис")));
    CHECK_FALSE(value.accepts(unknown));
}
