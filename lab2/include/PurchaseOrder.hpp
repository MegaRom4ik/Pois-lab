#pragma once
#include "Budget.hpp"
#include "OrderError.hpp"
#include "ShoppingList.hpp"
#include "Supplier.hpp"
#include "Support.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** Заказ поставщику с оплатой и отменой. */
class PurchaseOrder {
  public:
    PurchaseOrder(Supplier supplier = Supplier{}, ShoppingList list = ShoppingList{}, bool paid = false,
                  bool cancelled = false);
    const Supplier &supplier() const { return supplier_; }
    const ShoppingList &list() const { return list_; }
    bool paid() const { return paid_; }
    bool cancelled() const { return cancelled_; }
    void submit(Budget &budget);
    void cancel(Budget &budget);

  private:
    Supplier supplier_;
    ShoppingList list_;
    bool paid_;
    bool cancelled_;
};
} // namespace cooking
