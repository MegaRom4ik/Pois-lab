#include "Achievement.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw GoalError(message);
}
} // namespace
Achievement::Achievement(const std::string &name, int required_sessions, long long required_steps)
    : name_(name), required_sessions_(required_sessions), required_steps_(required_steps) {
    valid(!name_.empty() && required_sessions_ >= 0 && required_steps_ >= 0, "Invalid achievement");
}
bool Achievement::unlocked(const WorkoutLog &log, const StepHistory &steps, int last_day) const {
    return log.count_between(0, last_day) >= required_sessions_ &&
           steps.total_steps(0, last_day) >= required_steps_;
}
int Achievement::sessions_remaining(const WorkoutLog &log, int last_day) const {
    return std::max(0, required_sessions_ - log.count_between(0, last_day));
}
} // namespace fitness
