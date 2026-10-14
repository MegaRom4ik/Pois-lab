#pragma once
#include "RecipeError.hpp"
#include "Support.hpp"
#include "WorkflowError.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** Шаг приготовления с длительностью и зависимостью. */
class RecipeStep {
  public:
    RecipeStep(std::string instruction = "Смешать", int minutes = 5, int prerequisite = -1);
    const std::string &instruction() const { return instruction_; }
    int minutes() const { return minutes_; }
    int prerequisite() const { return prerequisite_; }
    bool ready(int completed_steps) const;
    int finish_at(int start_minute) const;

  private:
    std::string instruction_;
    int minutes_;
    int prerequisite_;
};
} // namespace cooking
