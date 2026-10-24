#pragma once
#include "Distance.hpp"
#include "GoalError.hpp"
#include "Support.hpp"
namespace fitness {
/** Daily step count and measured distance. */
class StepEntry {
  public:
    StepEntry(int day = 0, int steps = 1000, const Distance &distance = Distance(700));
    /** Read day. */
    const int &day() const { return day_; }
    /** Read steps. */
    const int &steps() const { return steps_; }
    /** Read distance. */
    const Distance &distance() const { return distance_; }
    /** Calculate average distance per step. */
    double stride_meters() const;
    /** Calculate steps remaining to a daily target. */
    int remaining(int target) const;

  private:
    int day_;
    int steps_;
    Distance distance_;
};
} // namespace fitness
