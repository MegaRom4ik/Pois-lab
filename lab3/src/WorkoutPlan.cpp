#include "WorkoutPlan.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw PlanError(message);
}
} // namespace
WorkoutPlan::WorkoutPlan(const std::string &name, const std::vector<Workout> &workouts, int weeks)
    : name_(name), workouts_(workouts), weeks_(weeks) {
    valid(!name_.empty() && weeks_ > 0, "Invalid workout plan");
}
void WorkoutPlan::add(const Workout &workout) { workouts_.push_back(workout); }
long long WorkoutPlan::planned_sessions() const { return static_cast<long long>(workouts_.size()) * weeks_; }
double WorkoutPlan::planned_volume() const {
    double weekly = 0;
    for (const auto &workout : workouts_)
        weekly += workout.lifted_volume();
    return weekly * weeks_;
}
} // namespace fitness
