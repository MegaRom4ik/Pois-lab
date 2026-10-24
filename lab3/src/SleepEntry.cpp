#include "SleepEntry.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw RecoveryError(message);
}
} // namespace
SleepEntry::SleepEntry(int day, int bedtime, int wake_time, int interruptions)
    : day_(day), bedtime_(bedtime), wake_time_(wake_time), interruptions_(interruptions) {
    valid(day_ >= 0 && bedtime_ >= 0 && bedtime_ < minutes_per_day && wake_time_ >= 0 &&
              wake_time_ < minutes_per_day && interruptions_ >= 0 && bedtime_ != wake_time_,
          "Invalid sleep entry");
}
int SleepEntry::minutes() const { return (wake_time_ - bedtime_ + minutes_per_day) % minutes_per_day; }
double SleepEntry::hours_per_interruption() const {
    return static_cast<double>(minutes()) / 60 / (interruptions_ + 1);
}
} // namespace fitness
