#pragma once
#include "IngredientAmount.hpp"
#include "Quantity.hpp"
#include "Support.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** A seasoning mixture with a recommended dose in the model. */
class SeasoningBlend {
  public:
    SeasoningBlend(std::string name = "Травы", std::vector<IngredientAmount> components = {IngredientAmount{}},
                   double grams_per_kg = 5);
    const std::string &name() const { return name_; }
    const std::vector<IngredientAmount> &components() const { return components_; }
    double grams_per_kg() const { return grams_per_kg_; }
    Quantity dose(const Quantity &food) const;
    double component_share(const std::string &name) const;

  private:
    std::string name_;
    std::vector<IngredientAmount> components_;
    double grams_per_kg_;
};
} // namespace cooking
