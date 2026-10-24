#include "SleepDiary.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw RecoveryError(message);
}
} // namespace
SleepDiary::SleepDiary(const std::vector<SleepEntry> &entries, int target_minutes, const std::string &owner)
    : entries_(entries), target_minutes_(target_minutes), owner_(owner) {
    valid(target_minutes_ > 0 && !owner_.empty(), "Invalid sleep diary");
    auto initial = entries_;
    entries_.clear();
    for (const auto &entry : initial)
        record(entry);
}
void SleepDiary::record(const SleepEntry &entry) {
    for (const auto &stored : entries_)
        valid(stored.day() != entry.day(), "Duplicate sleep day");
    entries_.push_back(entry);
}
double SleepDiary::average_hours() const {
    if (entries_.empty()) return 0;
    double total = 0;
    for (const auto &entry : entries_)
        total += entry.minutes();
    return total / entries_.size() / 60;
}
int SleepDiary::total_deficit() const {
    int total = 0;
    for (const auto &entry : entries_)
        total += std::max(0, target_minutes_ - entry.minutes());
    return total;
}
} // namespace fitness
