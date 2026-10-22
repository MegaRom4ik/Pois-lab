#pragma once
#include "InvalidQuantityError.hpp"
#include "Support.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** Ingredient mass in grams, including the edible yield. */
class Quantity {
  public:
    Quantity(double grams = 100, double yield = 1, std::string label = "г");
    double grams() const { return grams_; }
    double yield() const { return yield_; }
    const std::string &label() const { return label_; }
    Quantity scaled(double factor) const;
    double edible() const;
    Quantity combined(const Quantity &other) const;

  private:
    double grams_;
    double yield_;
    std::string label_;
};
} // namespace cooking
