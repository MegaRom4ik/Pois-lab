#pragma once
#include "Recipe.hpp"
#include "RecipeError.hpp"
#include "Support.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** Расчёт порций с резервом и запасом выхода. */
class PortionPlan {
  public:
    PortionPlan(int guests = 4, int reserve = 1, double yield = .9);
    int guests() const { return guests_; }
    int reserve() const { return reserve_; }
    double yield() const { return yield_; }
    int required() const;
    Recipe prepare(const Recipe &recipe) const;

  private:
    int guests_;
    int reserve_;
    double yield_;
};
} // namespace cooking
