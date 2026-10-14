#pragma once
#include "Oven.hpp"
#include "RecipeError.hpp"
#include "Support.hpp"
#include "WorkflowError.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** Режим выпечки и проверка духовки. */
class BakingProfile {
  public:
    BakingProfile(std::string name = "Хлеб", double temperature = 180, int minutes = 30);
    const std::string &name() const { return name_; }
    double temperature() const { return temperature_; }
    int minutes() const { return minutes_; }
    void prepare(Oven &oven) const;
    int finish_at(int start) const;

  private:
    std::string name_;
    double temperature_;
    int minutes_;
};
} // namespace cooking
