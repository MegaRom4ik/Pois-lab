#pragma once
#include "GoalError.hpp"
#include "StepHistory.hpp"
#include "Support.hpp"
#include "WorkoutLog.hpp"
namespace fitness {
/** A joint summary of workouts and step records. */
class ActivitySummary {
  public:
    ActivitySummary(const WorkoutLog &workouts = {}, const StepHistory &steps = {}, int day = 0);
    /** Read workouts. */
    const WorkoutLog &workouts() const { return workouts_; }
    /** Read steps. */
    const StepHistory &steps() const { return steps_; }
    /** Read day. */
    const int &day() const { return day_; }
    /** Count workouts in the trailing seven day window. */
    int weekly_sessions() const;
    /** Calculate average daily steps over the trailing available week. */
    double weekly_step_average() const;

  private:
    WorkoutLog workouts_;
    StepHistory steps_;
    int day_;
};
} // namespace fitness
