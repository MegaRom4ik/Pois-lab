#include "WeightHistory.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw MeasurementError(message);
}
} // namespace
WeightHistory::WeightHistory(const std::vector<WeightEntry> &entries, double target, double tolerance)
    : entries_(entries), target_(target), tolerance_(tolerance) {
    valid(target_ > 0 && tolerance_ >= 0 && std::isfinite(target_) && std::isfinite(tolerance_),
          "Invalid weight target");
    auto initial = entries_;
    entries_.clear();
    for (const auto &entry : initial)
        add(entry);
}
void WeightHistory::add(const WeightEntry &entry) {
    valid(entries_.empty() || entry.day() > entries_.back().day(), "Duplicate or unordered weight day");
    entries_.push_back(entry);
}
double WeightHistory::total_change() const {
    valid(!entries_.empty(), "No weight records");
    return entries_.back().kilograms() - entries_.front().kilograms();
}
bool WeightHistory::goal_reached() const {
    return !entries_.empty() && entries_.back().within(target_, tolerance_);
}
} // namespace fitness
