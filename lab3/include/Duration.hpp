#pragma once
#include "DurationError.hpp"
#include "Support.hpp"
namespace fitness {
/** Active, resting and paused time in seconds. */
class Duration {
  public:
    Duration(double active = 60, double rest = 0, double paused = 0);
    /** Read active. */
    const double &active() const { return active_; }
    /** Read rest. */
    const double &rest() const { return rest_; }
    /** Read paused. */
    const double &paused() const { return paused_; }
    /** Sum all recorded time. */
    double elapsed() const;
    /** Convert active time to minutes. */
    double active_minutes() const;
    /** Calculate the fraction spent active. */
    double active_share() const;

  private:
    double active_;
    double rest_;
    double paused_;
};
} // namespace fitness
