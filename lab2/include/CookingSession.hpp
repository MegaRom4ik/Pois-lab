#pragma once
#include "Dish.hpp"
#include "Pantry.hpp"
#include "Recipe.hpp"
#include "Support.hpp"
#include "WorkflowError.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** Приготовление по шагам с безопасным расходом склада. */
class CookingSession {
  public:
    CookingSession(Recipe recipe = Recipe{}, int next_step = 0, bool started = false, int day = 1);
    const Recipe &recipe() const { return recipe_; }
    int next_step() const { return next_step_; }
    bool started() const { return started_; }
    int day() const { return day_; }
    void begin(Pantry &pantry);
    void complete_step();
    Dish finish() const;

  private:
    Recipe recipe_;
    int next_step_;
    bool started_;
    int day_;
};
} // namespace cooking
