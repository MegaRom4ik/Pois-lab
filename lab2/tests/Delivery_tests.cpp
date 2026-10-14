#include "Budget.hpp"
#include "Delivery.hpp"
#include "OrderError.hpp"
#include "PurchaseOrder.hpp"
#include "ShoppingItem.hpp"
#include "ShoppingList.hpp"
#include "Supplier.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("Delivery: Приёмка поставки по дате и температуре.") {
    ShoppingList list;
    list.add(ShoppingItem{});
    Budget budget;
    PurchaseOrder order(Supplier{}, list);
    order.submit(budget);
    Delivery value(order);
    CHECK(value.on_time(2));
    CHECK_FALSE(value.on_time(1));
    value.accept(5);
    CHECK(value.accepted());
    CHECK_THROWS_AS(value.accept(5), OrderError);
    CHECK_THROWS_AS(Delivery{}.accept(5), OrderError);
}
