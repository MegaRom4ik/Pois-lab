#include "Participant.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw GoalError(message);
}
} // namespace
Participant::Participant(const std::string &name, const StepHistory &steps, const WorkoutLog &workouts)
    : name_(name), steps_(steps), workouts_(workouts) {
    valid(!name_.empty(), "Empty participant name");
}
long long Participant::step_score(int first, int last) const { return steps_.total_steps(first, last); }
int Participant::active_days(int first, int last) const {
    valid(first >= 0 && last >= first, "Invalid period");
    std::set<int> days;
    for (const auto &entry : steps_.entries())
        if (entry.day() >= first && entry.day() <= last && entry.steps() > 0) days.insert(entry.day());
    for (const auto &session : workouts_.sessions())
        if (session.in_period(first, last)) days.insert(session.day());
    return static_cast<int>(days.size());
}
} // namespace fitness
