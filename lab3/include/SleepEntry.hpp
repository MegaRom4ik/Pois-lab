#pragma once
#include "RecoveryError.hpp"
#include "Support.hpp"
namespace fitness {
/** A sleep interval expressed as minute of day. */
class SleepEntry {
  public:
    SleepEntry(int day = 0, int bedtime = 1380, int wake_time = 420, int interruptions = 0);
    /** Read day. */
    const int &day() const { return day_; }
    /** Read bedtime. */
    const int &bedtime() const { return bedtime_; }
    /** Read wake time. */
    const int &wake_time() const { return wake_time_; }
    /** Read interruptions. */
    const int &interruptions() const { return interruptions_; }
    /** Calculate duration, supporting an interval crossing midnight. */
    int minutes() const;
    /** Calculate average hours per uninterrupted segment. */
    double hours_per_interruption() const;

  private:
    int day_;
    int bedtime_;
    int wake_time_;
    int interruptions_;
};
} // namespace fitness
