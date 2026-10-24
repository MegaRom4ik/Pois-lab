#include "TrainingCalendar.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw ScheduleError(message);
}
} // namespace
TrainingCalendar::TrainingCalendar(const std::string &name, const std::vector<ScheduleSlot> &slots,
                                   int daily_limit)
    : name_(name), slots_(slots), daily_limit_(daily_limit) {
    valid(!name_.empty() && daily_limit_ > 0, "Invalid calendar");
    auto initial = slots_;
    slots_.clear();
    for (const auto &slot : initial)
        book(slot);
}
void TrainingCalendar::book(const ScheduleSlot &slot) {
    for (const auto &stored : slots_)
        valid(!stored.overlaps(slot), "Overlapping workouts");
    valid(minutes_on(slot.day()) + slot.duration_minutes() <= daily_limit_, "Daily training limit exceeded");
    slots_.push_back(slot);
}
int TrainingCalendar::minutes_on(int day) const {
    valid(day >= 0, "Invalid day");
    int total = 0;
    for (const auto &slot : slots_)
        if (slot.day() == day) total += slot.duration_minutes();
    return total;
}
void TrainingCalendar::cancel_day(int day) {
    valid(day >= 0, "Invalid day");
    slots_.erase(
        std::remove_if(slots_.begin(), slots_.end(), [day](const auto &slot) { return slot.day() == day; }),
        slots_.end());
}
} // namespace fitness
