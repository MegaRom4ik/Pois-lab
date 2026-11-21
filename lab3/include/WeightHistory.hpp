#pragma once
#include "MeasurementError.hpp"
#include "Support.hpp"
#include "WeightEntry.hpp"
namespace fitness {
/** Chronological weight records and a user selected target. */
class WeightHistory {
  public:
    WeightHistory(const std::vector<WeightEntry> &entries = {}, double target = 70, double tolerance = 1);
    /** Read entries. */
    const std::vector<WeightEntry> &entries() const { return entries_; }
    /** Read target. */
    const double &target() const { return target_; }
    /** Read tolerance. */
    const double &tolerance() const { return tolerance_; }
    /** Append a measurement with a new later day. */
    void add(const WeightEntry &entry);
    /** Calculate change between the first and last measurements. */
    double total_change() const;
    /** Check the latest measurement against the goal. */
    bool goal_reached() const;

  private:
    std::vector<WeightEntry> entries_;
    double target_;
    double tolerance_;
};
} // namespace fitness
