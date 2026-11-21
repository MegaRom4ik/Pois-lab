#pragma once
#include "Duration.hpp"
#include "PlanError.hpp"
#include "Support.hpp"
namespace fitness {
/** A repeated work and recovery block. */
class Interval {
  public:
    Interval(const Duration &work = Duration(60), const Duration &recovery = Duration(30),
             int repetitions = 4);
    /** Read work. */
    const Duration &work() const { return work_; }
    /** Read recovery. */
    const Duration &recovery() const { return recovery_; }
    /** Read repetitions. */
    const int &repetitions() const { return repetitions_; }
    /** Calculate block duration including every recovery. */
    double total_seconds() const;
    /** Calculate active work time across repetitions. */
    double work_seconds() const;

  private:
    Duration work_;
    Duration recovery_;
    int repetitions_;
};
} // namespace fitness
