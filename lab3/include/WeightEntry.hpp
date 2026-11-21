#pragma once
#include "MeasurementError.hpp"
#include "Support.hpp"
namespace fitness {
/** A dated weight measurement. */
class WeightEntry {
  public:
    WeightEntry(int day = 0, double kilograms = 70, const std::string &note = "");
    /** Read day. */
    const int &day() const { return day_; }
    /** Read kilograms. */
    const double &kilograms() const { return kilograms_; }
    /** Read note. */
    const std::string &note() const { return note_; }
    /** Calculate chronological weight change. */
    double change_from(const WeightEntry &previous) const;
    /** Compare a measurement with a target interval. */
    bool within(double target, double tolerance) const;

  private:
    int day_;
    double kilograms_;
    std::string note_;
};
} // namespace fitness
