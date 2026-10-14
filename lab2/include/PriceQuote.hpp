#pragma once
#include "OrderError.hpp"
#include "Quantity.hpp"
#include "Support.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** Предложение цены за килограмм продукта. */
class PriceQuote {
  public:
    PriceQuote(std::string ingredient = "мука", double per_kg = 100, int valid_until = 30);
    const std::string &ingredient() const { return ingredient_; }
    double per_kg() const { return per_kg_; }
    int valid_until() const { return valid_until_; }
    double cost(const Quantity &amount, int day) const;
    bool cheaper_than(const PriceQuote &other) const;

  private:
    std::string ingredient_;
    double per_kg_;
    int valid_until_;
};
} // namespace cooking
