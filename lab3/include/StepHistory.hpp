#pragma once
#include "GoalError.hpp"
#include "StepEntry.hpp"
#include "Support.hpp"
namespace fitness {
/** Unique daily step totals. */
class StepHistory {
  public:
    StepHistory(const std::vector<StepEntry> &entries = {}, const std::string &owner = "User",
                int daily_goal = 8000);
    /** Read entries. */
    const std::vector<StepEntry> &entries() const { return entries_; }
    /** Read owner. */
    const std::string &owner() const { return owner_; }
    /** Read daily goal. */
    const int &daily_goal() const { return daily_goal_; }
    /** Record the total for a new day. */
    void record(const StepEntry &entry);
    /** Sum steps over an inclusive day range. */
    long long total_steps(int first, int last) const;
    /** Count days meeting the configured step goal. */
    int goal_days() const;

  private:
    std::vector<StepEntry> entries_;
    std::string owner_;
    int daily_goal_;
};
} // namespace fitness
