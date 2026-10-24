#include "StepGoal.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw GoalError(message);
}
} // namespace
StepGoal::StepGoal(long long target, int first_day, int last_day)
    : target_(target), first_day_(first_day), last_day_(last_day) {
    valid(target_ > 0 && first_day_ >= 0 && last_day_ >= first_day_, "Invalid step goal");
}
double StepGoal::progress(const StepHistory &history) const {
    return std::min(1.0, static_cast<double>(history.total_steps(first_day_, last_day_)) / target_);
}
bool StepGoal::achieved(const StepHistory &history, int day) const {
    return day >= first_day_ && day <= last_day_ && history.total_steps(first_day_, day) >= target_;
}
} // namespace fitness
