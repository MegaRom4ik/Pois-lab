#include "Reminder.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw ScheduleError(message);
}
} // namespace
Reminder::Reminder(const std::string &message, int day, int minute, bool enabled)
    : message_(message), day_(day), minute_(minute), enabled_(enabled) {
    valid(!message_.empty() && day_ >= 0 && minute_ >= 0 && minute_ < minutes_per_day, "Invalid reminder");
}
bool Reminder::due(int day, int minute) const {
    valid(day >= 0 && minute >= 0 && minute < minutes_per_day, "Invalid reminder clock");
    return enabled_ && (day > day_ || (day == day_ && minute >= minute_));
}
void Reminder::postpone(int days) {
    valid(days > 0 && day_ <= std::numeric_limits<int>::max() - days, "Invalid postponement");
    day_ += days;
}
void Reminder::dismiss() { enabled_ = false; }
} // namespace fitness
