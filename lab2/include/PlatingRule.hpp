#pragma once
#include "Quantity.hpp"
#include "RecipeError.hpp"
#include "Support.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** Serving quantities for food and garnish. */
class PlatingRule {
  public:
    PlatingRule(std::string style = "Домашняя", double portion_grams = 250, double garnish_grams = 10);
    const std::string &style() const { return style_; }
    double portion_grams() const { return portion_grams_; }
    double garnish_grams() const { return garnish_grams_; }
    Quantity for_guests(int count) const;
    int plates_from(const Quantity &cooked) const;

  private:
    std::string style_;
    double portion_grams_;
    double garnish_grams_;
};
} // namespace cooking
