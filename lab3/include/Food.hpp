#pragma once
#include "Nutrients.hpp"
#include "NutritionError.hpp"
#include "Support.hpp"
namespace fitness {
/** A consumed portion with nutrition stated per 100 grams. */
class Food {
  public:
    Food(const std::string &name = "Food", const Nutrients &per_100g = {}, double grams = 100);
    /** Read name. */
    const std::string &name() const { return name_; }
    /** Read per 100g. */
    const Nutrients &per_100g() const { return per_100g_; }
    /** Read grams. */
    const double &grams() const { return grams_; }
    /** Convert reference nutrient values to the consumed portion. */
    Nutrients portion_nutrients() const;
    /** Create a portion of a different mass. */
    Food resized(double grams) const;

  private:
    std::string name_;
    Nutrients per_100g_;
    double grams_;
};
} // namespace fitness
