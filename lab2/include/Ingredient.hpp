#pragma once
#include "Allergen.hpp"
#include "Nutrition.hpp"
#include "Quantity.hpp"
#include "Support.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** A food ingredient with nutritional values and allergens. */
class Ingredient {
  public:
    Ingredient(std::string name = "мука", Nutrition nutrition = Nutrition{}, std::vector<std::string> allergens = {},
               bool vegetarian = true);
    const std::string &name() const { return name_; }
    const Nutrition &nutrition() const { return nutrition_; }
    const std::vector<std::string> &allergens() const { return allergens_; }
    bool vegetarian() const { return vegetarian_; }
    Nutrition nutrition_for(const Quantity &amount) const;
    bool contains(const Allergen &allergen) const;

  private:
    std::string name_;
    Nutrition nutrition_;
    std::vector<std::string> allergens_;
    bool vegetarian_;
};
} // namespace cooking
