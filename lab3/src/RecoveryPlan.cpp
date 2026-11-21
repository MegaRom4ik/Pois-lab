#include "RecoveryPlan.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw RecoveryError(message);
}
} // namespace
RecoveryPlan::RecoveryPlan(const std::string &name, int minimum_rest_days, int first_day)
    : name_(name), minimum_rest_days_(minimum_rest_days), first_day_(first_day) {
    valid(!name_.empty() && minimum_rest_days_ >= 0 && minimum_rest_days_ <= days_per_week &&
              first_day_ >= 0 && first_day_ <= std::numeric_limits<int>::max() - days_per_week,
          "Invalid recovery plan");
}
int RecoveryPlan::rest_days(const TrainingCalendar &calendar) const {
    int total = 0;
    for (int offset = 0; offset < days_per_week; ++offset)
        if (calendar.minutes_on(first_day_ + offset) == 0) ++total;
    return total;
}
bool RecoveryPlan::respected(const TrainingCalendar &calendar) const {
    return rest_days(calendar) >= minimum_rest_days_;
}
} // namespace fitness
