#include "ActivitySummary.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw GoalError(message);
}
} // namespace
ActivitySummary::ActivitySummary(const WorkoutLog &workouts, const StepHistory &steps, int day)
    : workouts_(workouts), steps_(steps), day_(day) {
    valid(day_ >= 0, "Invalid summary day");
}
int ActivitySummary::weekly_sessions() const {
    return workouts_.count_between(std::max(0, day_ - days_per_week + 1), day_);
}
double ActivitySummary::weekly_step_average() const {
    const int first = std::max(0, day_ - days_per_week + 1);
    return static_cast<double>(steps_.total_steps(first, day_)) / (day_ - first + 1);
}
} // namespace fitness
