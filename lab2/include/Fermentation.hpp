#pragma once
#include "Dough.hpp"
#include "RecipeError.hpp"
#include "Support.hpp"
#include "WorkflowError.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** An educational estimate of dough readiness based on time. */
class Fermentation {
  public:
    Fermentation(Dough dough = Dough{}, int required_minutes = 60, int elapsed_minutes = 0);
    const Dough &dough() const { return dough_; }
    int required_minutes() const { return required_minutes_; }
    int elapsed_minutes() const { return elapsed_minutes_; }
    void advance(int minutes);
    bool ready() const;
    double progress() const;

  private:
    Dough dough_;
    int required_minutes_;
    int elapsed_minutes_;
};
} // namespace cooking
