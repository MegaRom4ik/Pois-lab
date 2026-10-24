#pragma once
#include "GoalError.hpp"
#include "StepHistory.hpp"
#include "Support.hpp"
#include "WorkoutLog.hpp"
namespace fitness {
/** An achievement combining workout and step milestones. */
class Achievement {
  public:
    Achievement(const std::string &name = "Active week", int required_sessions = 3,
                long long required_steps = 30000);
    /** Read name. */
    const std::string &name() const { return name_; }
    /** Read required sessions. */
    const int &required_sessions() const { return required_sessions_; }
    /** Read required steps. */
    const long long &required_steps() const { return required_steps_; }
    /** Check both lifetime milestone requirements. */
    bool unlocked(const WorkoutLog &log, const StepHistory &steps, int last_day) const;
    /** Calculate workouts still needed for the achievement. */
    int sessions_remaining(const WorkoutLog &log, int last_day) const;

  private:
    std::string name_;
    int required_sessions_;
    long long required_steps_;
};
} // namespace fitness
