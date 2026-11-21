#pragma once
#include "NutritionError.hpp"
#include "Support.hpp"
namespace fitness {
/** A dated serving of water. */
class WaterEntry {
  public:
    WaterEntry(int day = 0, double milliliters = 250, const std::string &label = "Water");
    /** Read day. */
    const int &day() const { return day_; }
    /** Read milliliters. */
    const double &milliliters() const { return milliliters_; }
    /** Read label. */
    const std::string &label() const { return label_; }
    /** Convert the water serving to litres. */
    double liters() const;
    /** Count complete cups of a selected capacity. */
    double cups(double cup_ml) const;

  private:
    int day_;
    double milliliters_;
    std::string label_;
};
} // namespace fitness
