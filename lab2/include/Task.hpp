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
/** Задание повару с крайним сроком. */
class Task {
  public:
    Task(Recipe recipe = Recipe{}, int deadline = 60, bool completed = false);
    const Recipe &recipe() const { return recipe_; }
    int deadline() const { return deadline_; }
    bool completed() const { return completed_; }
    bool fits(int start) const;
    void complete(int finish);

  private:
    Recipe recipe_;
    int deadline_;
    bool completed_;
};
} // namespace cooking
