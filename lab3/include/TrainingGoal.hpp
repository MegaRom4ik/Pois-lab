#pragma once
#include "GoalError.hpp"
#include "Support.hpp"
#include "WorkoutLog.hpp"
namespace fitness {
/** A workout attendance target in a date interval. */
class TrainingGoal {
  public:
    TrainingGoal(int required_sessions = 3, int first_day = 0, int last_day = 6);
    /** Read required sessions. */
    const int &required_sessions() const { return required_sessions_; }
    /** Read first day. */
    const int &first_day() const { return first_day_; }
    /** Read last day. */
    const int &last_day() const { return last_day_; }
    /** Calculate the attendance shortfall for the chosen period. */
    int sessions_missing(const WorkoutLog &log) const;
    /** Calculate capped attendance completion as a percentage. */
    double completion_percent(const WorkoutLog &log) const;

  private:
    int required_sessions_;
    int first_day_;
    int last_day_;
};
} // namespace fitness
