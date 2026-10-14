#pragma once
#include "Ingredient.hpp"
#include "Quantity.hpp"
#include "Support.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** Перевод массы в объём по плотности. */
class UnitConversion {
  public:
    UnitConversion(Ingredient ingredient = Ingredient{}, double grams_per_ml = .6, std::string volume_unit = "мл");
    const Ingredient &ingredient() const { return ingredient_; }
    double grams_per_ml() const { return grams_per_ml_; }
    const std::string &volume_unit() const { return volume_unit_; }
    double volume_for(const Quantity &amount) const;
    Quantity mass_for(double volume) const;

  private:
    Ingredient ingredient_;
    double grams_per_ml_;
    std::string volume_unit_;
};
} // namespace cooking
