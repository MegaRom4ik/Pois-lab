#include "Budget.hpp"
#include "BudgetError.hpp"
#include "ShoppingItem.hpp"
#include "ShoppingList.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("Budget: Бюджет закупок и учёт возвратов.") {
    Budget value(100);
    ShoppingList list;
    list.add(ShoppingItem{});
    CHECK(value.covers(list));
    value.pay(80);
    CHECK(value.spent() == 80);
    CHECK_THROWS_AS(value.pay(30), BudgetError);
    value.refund(20);
    CHECK(value.spent() == 60);
    CHECK_THROWS_AS(value.refund(70), BudgetError);
}
