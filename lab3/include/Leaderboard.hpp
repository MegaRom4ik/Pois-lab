#pragma once
#include "GoalError.hpp"
#include "Participant.hpp"
#include "Support.hpp"
namespace fitness {
/** A deterministic ranking by step totals. */
class Leaderboard {
  public:
    Leaderboard(const std::string &name = "Weekly steps", const std::vector<Participant> &participants = {},
                int first_day = 0);
    /** Read name. */
    const std::string &name() const { return name_; }
    /** Read participants. */
    const std::vector<Participant> &participants() const { return participants_; }
    /** Read first day. */
    const int &first_day() const { return first_day_; }
    /** Register a participant with a unique display name. */
    void join(const Participant &participant);
    /** Rank descending step totals, resolving ties alphabetically. */
    std::vector<std::string> ranking(int last_day) const;

  private:
    std::string name_;
    std::vector<Participant> participants_;
    int first_day_;
};
} // namespace fitness
