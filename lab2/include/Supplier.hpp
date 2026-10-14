#pragma once
#include "OrderError.hpp"
#include "PriceQuote.hpp"
#include "ShoppingList.hpp"
#include "Support.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** Поставщик с ассортиментом и минимальной суммой заказа. */
class Supplier {
  public:
    Supplier(std::string name = "Ферма", std::vector<PriceQuote> offers = {PriceQuote{}}, double minimum_order = 10);
    const std::string &name() const { return name_; }
    const std::vector<PriceQuote> &offers() const { return offers_; }
    double minimum_order() const { return minimum_order_; }
    PriceQuote quote_for(const std::string &product) const;
    bool accepts(const ShoppingList &list) const;

  private:
    std::string name_;
    std::vector<PriceQuote> offers_;
    double minimum_order_;
};
} // namespace cooking
