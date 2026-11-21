#pragma once
#include "Meal.hpp"
#include "NutritionError.hpp"
#include "Support.hpp"
namespace fitness {
/** A food diary with a user selected energy budget. */
class FoodDiary {
  public:
    FoodDiary(const std::vector<Meal> &meals = {}, double target_kcal = 2000,
              const std::string &owner = "User");
    /** Read meals. */
    const std::vector<Meal> &meals() const { return meals_; }
    /** Read target kcal. */
    const double &target_kcal() const { return target_kcal_; }
    /** Read owner. */
    const std::string &owner() const { return owner_; }
    /** Record a consumed meal. */
    void record(const Meal &meal);
    /** Sum recorded food energy for a day. */
    double calories_on(int day) const;
    /** Calculate remaining energy relative to the user chosen budget. */
    double budget_balance(int day) const;

  private:
    std::vector<Meal> meals_;
    double target_kcal_;
    std::string owner_;
};
} // namespace fitness
