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
/** Строка рецепта: продукт, количество и обязательность. */
class IngredientAmount {
  public:
    IngredientAmount(Ingredient ingredient = Ingredient{}, Quantity amount = Quantity{}, bool optional = false);
    const Ingredient &ingredient() const { return ingredient_; }
    const Quantity &amount() const { return amount_; }
    bool optional() const { return optional_; }
    IngredientAmount scaled(double factor) const;
    double calories() const;

  private:
    Ingredient ingredient_;
    Quantity amount_;
    bool optional_;
};
} // namespace cooking
