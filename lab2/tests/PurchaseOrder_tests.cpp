#include "Budget.hpp"
#include "OrderError.hpp"
#include "PurchaseOrder.hpp"
#include "ShoppingItem.hpp"
#include "ShoppingList.hpp"
#include "Supplier.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("PurchaseOrder: Заказ поставщику с оплатой и отменой.") {
    ShoppingList list;
    list.add(ShoppingItem{});
    Budget budget;
    PurchaseOrder value(Supplier{}, list);
    value.submit(budget);
    CHECK(value.paid());
    CHECK_THROWS_AS(value.submit(budget), OrderError);
    value.cancel(budget);
    CHECK(budget.spent() == 0);
    CHECK_THROWS_AS(value.cancel(budget), OrderError);
    PurchaseOrder pending;
    pending.cancel(budget);
}
