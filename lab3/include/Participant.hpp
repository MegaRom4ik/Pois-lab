#pragma once
#include "GoalError.hpp"
#include "StepHistory.hpp"
#include "Support.hpp"
#include "WorkoutLog.hpp"
namespace fitness {
/** A leaderboard participant with independent activity history. */
class Participant {
  public:
    Participant(const std::string &name = "User", const StepHistory &steps = {},
                const WorkoutLog &workouts = {});
    /** Read name. */
    const std::string &name() const { return name_; }
    /** Read steps. */
    const StepHistory &steps() const { return steps_; }
    /** Read workouts. */
    const WorkoutLog &workouts() const { return workouts_; }
    /** Calculate a participant score using step totals only. */
    long long step_score(int first, int last) const;
    /** Count distinct days with steps or a completed workout. */
    int active_days(int first, int last) const;

  private:
    std::string name_;
    StepHistory steps_;
    WorkoutLog workouts_;
};
} // namespace fitness
