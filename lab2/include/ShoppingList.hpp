#pragma once
#include "OrderError.hpp"
#include "ShoppingItem.hpp"
#include "Support.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** A shopping list with an item limit. */
class ShoppingList {
  public:
    ShoppingList(std::string title = "Закупка", std::vector<ShoppingItem> items = {}, int limit = 100);
    const std::string &title() const { return title_; }
    const std::vector<ShoppingItem> &items() const { return items_; }
    int limit() const { return limit_; }
    void add(const ShoppingItem &item);
    double total() const;
    void remove_product(const std::string &name);

  private:
    std::string title_;
    std::vector<ShoppingItem> items_;
    int limit_;
};
} // namespace cooking
