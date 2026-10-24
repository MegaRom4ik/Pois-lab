#pragma once
#include "Distance.hpp"
#include "DistanceError.hpp"
#include "Duration.hpp"
#include "Support.hpp"
namespace fitness {
/** A numbered cardio split. */
class Lap {
  public:
    Lap(int number = 1, const Distance &distance = {}, const Duration &duration = Duration(300));
    /** Read number. */
    const int &number() const { return number_; }
    /** Read distance. */
    const Distance &distance() const { return distance_; }
    /** Read duration. */
    const Duration &duration() const { return duration_; }
    /** Normalize split timing to 100 metres. */
    double seconds_per_100m() const;
    /** Compare active time for equal distance splits. */
    double time_difference(const Lap &other) const;

  private:
    int number_;
    Distance distance_;
    Duration duration_;
};
} // namespace fitness
