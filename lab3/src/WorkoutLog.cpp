#include "WorkoutLog.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw WorkoutError(message);
}
} // namespace
WorkoutLog::WorkoutLog(const std::vector<WorkoutSession> &sessions, const std::string &owner, int capacity)
    : sessions_(sessions), owner_(owner), capacity_(capacity) {
    valid(!owner_.empty() && capacity_ > 0, "Invalid workout log");
    auto initial = sessions_;
    sessions_.clear();
    for (const auto &session : initial)
        append(session);
}
void WorkoutLog::append(const WorkoutSession &session) {
    valid(session.completed(), "Only completed sessions can be logged");
    valid(sessions_.size() < static_cast<std::size_t>(capacity_), "Workout log full");
    for (const auto &stored : sessions_)
        valid(stored.id() != session.id(), "Duplicate session ID");
    sessions_.push_back(session);
}
double WorkoutLog::volume_between(int first, int last) const {
    valid(first >= 0 && last >= first, "Invalid period");
    double total = 0;
    for (const auto &session : sessions_)
        if (session.in_period(first, last)) total += session.workout().lifted_volume();
    return total;
}
int WorkoutLog::count_between(int first, int last) const {
    valid(first >= 0 && last >= first, "Invalid period");
    int total = 0;
    for (const auto &session : sessions_)
        if (session.in_period(first, last)) ++total;
    return total;
}
} // namespace fitness
