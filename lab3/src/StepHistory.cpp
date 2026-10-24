#include "StepHistory.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw GoalError(message);
}
} // namespace
StepHistory::StepHistory(const std::vector<StepEntry> &entries, const std::string &owner, int daily_goal)
    : entries_(entries), owner_(owner), daily_goal_(daily_goal) {
    valid(!owner_.empty() && daily_goal_ > 0, "Invalid step history");
    auto initial = entries_;
    entries_.clear();
    for (const auto &entry : initial)
        record(entry);
}
void StepHistory::record(const StepEntry &entry) {
    for (const auto &stored : entries_)
        valid(stored.day() != entry.day(), "Duplicate step day");
    entries_.push_back(entry);
}
long long StepHistory::total_steps(int first, int last) const {
    valid(first >= 0 && last >= first, "Invalid period");
    long long total = 0;
    for (const auto &entry : entries_)
        if (entry.day() >= first && entry.day() <= last) total += entry.steps();
    return total;
}
int StepHistory::goal_days() const {
    int total = 0;
    for (const auto &entry : entries_)
        if (entry.steps() >= daily_goal_) ++total;
    return total;
}
} // namespace fitness
