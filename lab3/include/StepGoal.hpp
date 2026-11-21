#pragma once
#include "GoalError.hpp"
#include "StepHistory.hpp"
#include "Support.hpp"
namespace fitness {
/** A step challenge over an inclusive date range. */
class StepGoal {
  public:
    StepGoal(long long target = 10000, int first_day = 0, int last_day = 6);
    /** Read target. */
    const long long &target() const { return target_; }
    /** Read first day. */
    const int &first_day() const { return first_day_; }
    /** Read last day. */
    const int &last_day() const { return last_day_; }
    /** Calculate capped progress over the challenge period. */
    double progress(const StepHistory &history) const;
    /** Check if the step target has been met before its deadline. */
    bool achieved(const StepHistory &history, int day) const;

  private:
    long long target_;
    int first_day_;
    int last_day_;
};
} // namespace fitness
