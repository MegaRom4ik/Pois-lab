#include "TrainingGoal.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw GoalError(message);
}
} // namespace
TrainingGoal::TrainingGoal(int required_sessions, int first_day, int last_day)
    : required_sessions_(required_sessions), first_day_(first_day), last_day_(last_day) {
    valid(required_sessions_ > 0 && first_day_ >= 0 && last_day_ >= first_day_, "Invalid training goal");
}
int TrainingGoal::sessions_missing(const WorkoutLog &log) const {
    return std::max(0, required_sessions_ - log.count_between(first_day_, last_day_));
}
double TrainingGoal::completion_percent(const WorkoutLog &log) const {
    return 100.0 * std::min(required_sessions_, log.count_between(first_day_, last_day_)) /
           required_sessions_;
}
} // namespace fitness
