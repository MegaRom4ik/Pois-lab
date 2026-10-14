#pragma once
#include "Quantity.hpp"
#include "RecipeError.hpp"
#include "SeasoningBlend.hpp"
#include "Support.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** План маринования по массе и времени. */
class Marinade {
  public:
    Marinade(SeasoningBlend blend = SeasoningBlend{}, int minutes_per_kg = 60, double liquid_ratio = .2);
    const SeasoningBlend &blend() const { return blend_; }
    int minutes_per_kg() const { return minutes_per_kg_; }
    double liquid_ratio() const { return liquid_ratio_; }
    int duration(const Quantity &food) const;
    Quantity liquid_for(const Quantity &food) const;

  private:
    SeasoningBlend blend_;
    int minutes_per_kg_;
    double liquid_ratio_;
};
} // namespace cooking
