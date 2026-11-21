#pragma once
#include "GoalError.hpp"
#include "StepGoal.hpp"
#include "StepHistory.hpp"
#include "Support.hpp"
namespace fitness {
/** A named, dated step challenge. */
class Challenge {
  public:
    Challenge(const std::string &name = "Steps", const StepGoal &goal = {},
              const std::string &reward = "Badge");
    /** Read name. */
    const std::string &name() const { return name_; }
    /** Read goal. */
    const StepGoal &goal() const { return goal_; }
    /** Read reward. */
    const std::string &reward() const { return reward_; }
    /** Award the configured label only after reaching the challenge goal. */
    std::string result(const StepHistory &history, int day) const;
    /** Calculate the step shortfall for the challenge period. */
    long long steps_missing(const StepHistory &history) const;

  private:
    std::string name_;
    StepGoal goal_;
    std::string reward_;
};
} // namespace fitness
