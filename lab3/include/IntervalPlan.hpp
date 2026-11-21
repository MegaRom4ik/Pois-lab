#pragma once
#include "Duration.hpp"
#include "Interval.hpp"
#include "PlanError.hpp"
#include "Support.hpp"
namespace fitness {
/** A warmup followed by interval blocks. */
class IntervalPlan {
  public:
    IntervalPlan(const std::string &name = "Intervals", const Duration &warmup = Duration(300),
                 const std::vector<Interval> &blocks = {});
    /** Read name. */
    const std::string &name() const { return name_; }
    /** Read warmup. */
    const Duration &warmup() const { return warmup_; }
    /** Read blocks. */
    const std::vector<Interval> &blocks() const { return blocks_; }
    /** Append an interval block. */
    void append(const Interval &block);
    /** Calculate the complete interval session duration. */
    double elapsed_minutes() const;
    /** Calculate the active work fraction including warmup. */
    double work_fraction() const;

  private:
    std::string name_;
    Duration warmup_;
    std::vector<Interval> blocks_;
};
} // namespace fitness
