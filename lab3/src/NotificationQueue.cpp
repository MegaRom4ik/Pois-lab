#include "NotificationQueue.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw ScheduleError(message);
}
} // namespace
NotificationQueue::NotificationQueue(const std::string &owner, const std::vector<Reminder> &reminders,
                                     int capacity)
    : owner_(owner), reminders_(reminders), capacity_(capacity) {
    valid(!owner_.empty() && capacity_ > 0 && reminders_.size() <= static_cast<std::size_t>(capacity_),
          "Invalid reminder queue");
}
void NotificationQueue::enqueue(const Reminder &reminder) {
    valid(reminders_.size() < static_cast<std::size_t>(capacity_), "Reminder queue full");
    reminders_.push_back(reminder);
}
std::vector<std::string> NotificationQueue::deliver(int day, int minute) {
    valid(day >= 0 && minute >= 0 && minute < minutes_per_day, "Invalid notification clock");
    std::vector<std::string> result;
    for (auto &reminder : reminders_)
        if (reminder.due(day, minute)) {
            result.push_back(reminder.message());
            reminder.dismiss();
        }
    return result;
}
} // namespace fitness
