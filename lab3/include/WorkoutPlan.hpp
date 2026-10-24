#pragma once
#include "PlanError.hpp"
#include "Support.hpp"
#include "Workout.hpp"
namespace fitness {
/** A weekly workout pattern repeated for a number of weeks. */
class WorkoutPlan {
  public:
    WorkoutPlan(const std::string &name = "Plan", const std::vector<Workout> &workouts = {}, int weeks = 4);
    /** Read name. */
    const std::string &name() const { return name_; }
    /** Read workouts. */
    const std::vector<Workout> &workouts() const { return workouts_; }
    /** Read weeks. */
    const int &weeks() const { return weeks_; }
    /** Add a workout to the weekly pattern. */
    void add(const Workout &workout);
    /** Calculate the number of scheduled sessions. */
    long long planned_sessions() const;
    /** Calculate total planned lifted volume. */
    double planned_volume() const;

  private:
    std::string name_;
    std::vector<Workout> workouts_;
    int weeks_;
};
} // namespace fitness
