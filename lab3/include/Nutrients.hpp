#pragma once
#include "NutritionError.hpp"
#include "Support.hpp"
namespace fitness {
/** Macronutrient masses in grams. */
class Nutrients {
  public:
    Nutrients(double protein = 0, double fat = 0, double carbohydrate = 0);
    /** Read protein. */
    const double &protein() const { return protein_; }
    /** Read fat. */
    const double &fat() const { return fat_; }
    /** Read carbohydrate. */
    const double &carbohydrate() const { return carbohydrate_; }
    /** Calculate energy using 4, 9 and 4 kcal per gram. */
    double calories() const;
    /** Scale all nutrient masses together. */
    Nutrients scaled(double factor) const;
    /** Combine nutrients from multiple portions. */
    Nutrients combined(const Nutrients &other) const;

  private:
    double protein_;
    double fat_;
    double carbohydrate_;
};
} // namespace fitness
