#pragma once
#include "ScheduleError.hpp"
#include "Support.hpp"
namespace fitness {
/** A scheduled reminder that can be dismissed. */
class Reminder {
  public:
    Reminder(const std::string &message = "Workout", int day = 0, int minute = 600, bool enabled = true);
    /** Read message. */
    const std::string &message() const { return message_; }
    /** Read day. */
    const int &day() const { return day_; }
    /** Read minute. */
    const int &minute() const { return minute_; }
    /** Read enabled. */
    const bool &enabled() const { return enabled_; }
    /** Check whether an enabled reminder is due. */
    bool due(int day, int minute) const;
    /** Postpone a reminder by a positive number of days. */
    void postpone(int days);
    /** Disable further delivery of this reminder. */
    void dismiss();

  private:
    std::string message_;
    int day_;
    int minute_;
    bool enabled_;
};
} // namespace fitness
