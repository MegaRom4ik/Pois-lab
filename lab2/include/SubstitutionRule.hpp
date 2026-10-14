#pragma once
#include "DietProfile.hpp"
#include "Ingredient.hpp"
#include "IngredientAmount.hpp"
#include "IngredientError.hpp"
#include "Support.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** Замена продукта с коэффициентом массы. */
class SubstitutionRule {
  public:
    SubstitutionRule(std::string original = "молоко", Ingredient replacement = Ingredient("вода"), double ratio = 1);
    const std::string &original() const { return original_; }
    const Ingredient &replacement() const { return replacement_; }
    double ratio() const { return ratio_; }
    IngredientAmount apply(const IngredientAmount &item) const;
    bool compatible(const DietProfile &profile) const;

  private:
    std::string original_;
    Ingredient replacement_;
    double ratio_;
};
} // namespace cooking
