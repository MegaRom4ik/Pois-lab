#include "HydrationLog.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw NutritionError(message);
}
} // namespace
HydrationLog::HydrationLog(const std::vector<WaterEntry> &entries, double target_ml, const std::string &owner)
    : entries_(entries), target_ml_(target_ml), owner_(owner) {
    valid(target_ml_ > 0 && std::isfinite(target_ml_) && !owner_.empty(), "Invalid hydration log");
}
void HydrationLog::drink(const WaterEntry &entry) { entries_.push_back(entry); }
double HydrationLog::total_on(int day) const {
    valid(day >= 0, "Invalid day");
    double total = 0;
    for (const auto &entry : entries_)
        if (entry.day() == day) total += entry.milliliters();
    return total;
}
double HydrationLog::remaining_on(int day) const { return std::max(0.0, target_ml_ - total_on(day)); }
} // namespace fitness
