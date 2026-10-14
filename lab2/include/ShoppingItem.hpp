#pragma once
#include "IngredientAmount.hpp"
#include "OrderError.hpp"
#include "PriceQuote.hpp"
#include "Support.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** Позиция закупки с количеством и ценой. */
class ShoppingItem {
  public:
    ShoppingItem(IngredientAmount item = IngredientAmount{}, PriceQuote quote = PriceQuote{}, int day = 1);
    const IngredientAmount &item() const { return item_; }
    const PriceQuote &quote() const { return quote_; }
    int day() const { return day_; }
    double total() const;
    ShoppingItem increased(double factor) const;

  private:
    IngredientAmount item_;
    PriceQuote quote_;
    int day_;
};
} // namespace cooking
