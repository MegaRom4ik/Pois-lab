#pragma once
#include "AllergyError.hpp"
#include "DietProfile.hpp"
#include "Recipe.hpp"
#include "RecipeError.hpp"
#include "Support.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** A meal plan with a total calorie limit. */
class MealPlan {
  public:
    MealPlan(DietProfile profile = DietProfile{}, std::vector<Recipe> meals = {}, double daily_limit = 2000);
    const DietProfile &profile() const { return profile_; }
    const std::vector<Recipe> &meals() const { return meals_; }
    double daily_limit() const { return daily_limit_; }
    double calories() const;
    void add(const Recipe &recipe);

  private:
    DietProfile profile_;
    std::vector<Recipe> meals_;
    double daily_limit_;
};
} // namespace cooking
