#include "Challenge.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw GoalError(message);
}
} // namespace
Challenge::Challenge(const std::string &name, const StepGoal &goal, const std::string &reward)
    : name_(name), goal_(goal), reward_(reward) {
    valid(!name_.empty() && !reward_.empty(), "Invalid challenge");
}
std::string Challenge::result(const StepHistory &history, int day) const {
    return goal_.achieved(history, day) ? reward_ : std::string("Pending");
}
long long Challenge::steps_missing(const StepHistory &history) const {
    return std::max(0LL, goal_.target() - history.total_steps(goal_.first_day(), goal_.last_day()));
}
} // namespace fitness
