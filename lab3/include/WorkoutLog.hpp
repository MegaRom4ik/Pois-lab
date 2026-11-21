#pragma once
#include "Support.hpp"
#include "WorkoutError.hpp"
#include "WorkoutSession.hpp"
namespace fitness {
/** Completed workouts identified by unique session IDs. */
class WorkoutLog {
  public:
    WorkoutLog(const std::vector<WorkoutSession> &sessions = {}, const std::string &owner = "User",
               int capacity = 10000);
    /** Read sessions. */
    const std::vector<WorkoutSession> &sessions() const { return sessions_; }
    /** Read owner. */
    const std::string &owner() const { return owner_; }
    /** Read capacity. */
    const int &capacity() const { return capacity_; }
    /** Store a completed session after checking uniqueness and capacity. */
    void append(const WorkoutSession &session);
    /** Aggregate lifted volume for a period. */
    double volume_between(int first, int last) const;
    /** Count completed sessions in a period. */
    int count_between(int first, int last) const;

  private:
    std::vector<WorkoutSession> sessions_;
    std::string owner_;
    int capacity_;
};
} // namespace fitness
