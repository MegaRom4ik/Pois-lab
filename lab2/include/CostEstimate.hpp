#pragma once
#include "Recipe.hpp"
#include "ShoppingList.hpp"
#include "Support.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** Dish costs including ingredients, labor, and overhead. */
class CostEstimate {
  public:
    CostEstimate(ShoppingList products = ShoppingList{}, double labor_per_minute = 1, double overhead = 5);
    const ShoppingList &products() const { return products_; }
    double labor_per_minute() const { return labor_per_minute_; }
    double overhead() const { return overhead_; }
    double total(const Recipe &recipe) const;
    double per_serving(const Recipe &recipe) const;

  private:
    ShoppingList products_;
    double labor_per_minute_;
    double overhead_;
};
} // namespace cooking
