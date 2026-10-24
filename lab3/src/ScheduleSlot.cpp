#include "ScheduleSlot.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw ScheduleError(message);
}
} // namespace
ScheduleSlot::ScheduleSlot(int day, int minute, int duration_minutes, const Workout &workout)
    : day_(day), minute_(minute), duration_minutes_(duration_minutes), workout_(workout) {
    valid(day_ >= 0 && minute_ >= 0 && duration_minutes_ > 0 &&
              minute_ <= minutes_per_day - duration_minutes_,
          "Slot must fit in one day");
}
int ScheduleSlot::end_minute() const { return minute_ + duration_minutes_; }
bool ScheduleSlot::overlaps(const ScheduleSlot &other) const {
    return day_ == other.day_ && minute_ < other.end_minute() && other.minute_ < end_minute();
}
} // namespace fitness
