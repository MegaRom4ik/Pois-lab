#pragma once
#include "Reminder.hpp"
#include "ScheduleError.hpp"
#include "Support.hpp"
namespace fitness {
/** Bounded reminders for a single user. */
class NotificationQueue {
  public:
    NotificationQueue(const std::string &owner = "User", const std::vector<Reminder> &reminders = {},
                      int capacity = 100);
    /** Read owner. */
    const std::string &owner() const { return owner_; }
    /** Read reminders. */
    const std::vector<Reminder> &reminders() const { return reminders_; }
    /** Read capacity. */
    const int &capacity() const { return capacity_; }
    /** Queue a reminder without exceeding capacity. */
    void enqueue(const Reminder &reminder);
    /** Return and dismiss due reminders so they are delivered once. */
    std::vector<std::string> deliver(int day, int minute);

  private:
    std::string owner_;
    std::vector<Reminder> reminders_;
    int capacity_;
};
} // namespace fitness
