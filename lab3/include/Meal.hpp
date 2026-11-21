#pragma once
#include "Food.hpp"
#include "Nutrients.hpp"
#include "NutritionError.hpp"
#include "Support.hpp"
namespace fitness {
/** A dated meal containing food portions. */
class Meal {
  public:
    Meal(const std::string &name = "Meal", int day = 0, const std::vector<Food> &foods = {});
    /** Read name. */
    const std::string &name() const { return name_; }
    /** Read day. */
    const int &day() const { return day_; }
    /** Read foods. */
    const std::vector<Food> &foods() const { return foods_; }
    /** Add a food portion to the meal. */
    void add(const Food &food);
    /** Aggregate nutrients across food portions. */
    Nutrients total_nutrients() const;
    /** Calculate total consumed food mass. */
    double total_grams() const;

  private:
    std::string name_;
    int day_;
    std::vector<Food> foods_;
};
} // namespace fitness
