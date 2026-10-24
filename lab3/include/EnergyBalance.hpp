#pragma once
#include "NutritionError.hpp"
#include "Support.hpp"
namespace fitness {
/** User supplied daily intake and expenditure estimates. */
class EnergyBalance {
  public:
    EnergyBalance(double intake = 2000, double activity = 300, double baseline = 1700);
    /** Read intake. */
    const double &intake() const { return intake_; }
    /** Read activity. */
    const double &activity() const { return activity_; }
    /** Read baseline. */
    const double &baseline() const { return baseline_; }
    /** Subtract estimated expenditure from intake. */
    double net() const;
    /** Calculate the activity fraction of estimated expenditure. */
    double activity_share() const;

  private:
    double intake_;
    double activity_;
    double baseline_;
};
} // namespace fitness
