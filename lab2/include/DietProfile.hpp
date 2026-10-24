#pragma once
#include "Allergen.hpp"
#include "Ingredient.hpp"
#include "Recipe.hpp"
#include "Support.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** A user's dietary restrictions. */
class DietProfile {
  public:
    DietProfile(std::string person = "Гость", std::vector<Allergen> forbidden = {}, double calorie_limit = 800,
                bool vegetarian = false);
    const std::string &person() const { return person_; }
    const std::vector<Allergen> &forbidden() const { return forbidden_; }
    double calorie_limit() const { return calorie_limit_; }
    bool vegetarian() const { return vegetarian_; }
    bool allows(const Ingredient &ingredient) const;
    bool accepts(const Recipe &recipe) const;

  private:
    std::string person_;
    std::vector<Allergen> forbidden_;
    double calorie_limit_;
    bool vegetarian_;
};
} // namespace cooking
