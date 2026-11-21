#pragma once
#include "GoalError.hpp"
#include "StepHistory.hpp"
#include "Support.hpp"
#include "WeightHistory.hpp"
#include "WorkoutLog.hpp"
namespace fitness {
/** A report combining workouts, steps and weight history. */
class ProgressReport {
  public:
    ProgressReport(const WorkoutLog &workouts = {}, const StepHistory &steps = {},
                   const WeightHistory &weights = {});
    /** Read workouts. */
    const WorkoutLog &workouts() const { return workouts_; }
    /** Read steps. */
    const StepHistory &steps() const { return steps_; }
    /** Read weights. */
    const WeightHistory &weights() const { return weights_; }
    /** Render a dated activity summary and lifetime weight change. */
    std::string render(int first, int last) const;
    /** Normalize the session count to a seven day rate. */
    double sessions_per_week(int first, int last) const;

  private:
    WorkoutLog workouts_;
    StepHistory steps_;
    WeightHistory weights_;
};
} // namespace fitness
