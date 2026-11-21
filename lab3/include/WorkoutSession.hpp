#pragma once
#include "Support.hpp"
#include "Workout.hpp"
#include "WorkoutError.hpp"
namespace fitness {
/** A dated workout with explicit completion state. */
class WorkoutSession {
  public:
    WorkoutSession(int id = 1, const Workout &workout = {}, int day = 0, bool completed = false);
    /** Read id. */
    const int &id() const { return id_; }
    /** Read workout. */
    const Workout &workout() const { return workout_; }
    /** Read day. */
    const int &day() const { return day_; }
    /** Read completed. */
    const bool &completed() const { return completed_; }
    /** Complete a nonempty session once. */
    void finish();
    /** Select completed sessions within an inclusive date range. */
    bool in_period(int first, int last) const;

  private:
    int id_;
    Workout workout_;
    int day_;
    bool completed_;
};
} // namespace fitness
