#pragma once
#include "Recipe.hpp"
#include "Support.hpp"
#include "WorkflowError.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** A cooked dish with a remaining portion count. */
class Dish {
  public:
    Dish(Recipe recipe = Recipe{}, int remaining = 2, int cooked_day = 1);
    const Recipe &recipe() const { return recipe_; }
    int remaining() const { return remaining_; }
    int cooked_day() const { return cooked_day_; }
    void serve(int portions);
    double calories_for(int portions) const;

  private:
    Recipe recipe_;
    int remaining_;
    int cooked_day_;
};
} // namespace cooking
