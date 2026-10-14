#pragma once
#include "Support.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>

namespace cooking {
/** Пищевая ценность заданного количества продукта. */
class Nutrition {
  public:
    Nutrition(double calories = 100, double protein = 5, double fat = 3, double carbs = 10);
    double calories() const { return calories_; }
    double protein() const { return protein_; }
    double fat() const { return fat_; }
    double carbs() const { return carbs_; }
    Nutrition for_mass(double grams) const;
    Nutrition combined(const Nutrition &other) const;
    double macro_energy() const;

  private:
    double calories_;
    double protein_;
    double fat_;
    double carbs_;
};
} // namespace cooking
