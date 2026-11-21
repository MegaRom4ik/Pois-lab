#pragma once
#include "ScheduleError.hpp"
#include "ScheduleSlot.hpp"
#include "Support.hpp"
namespace fitness {
/** Nonoverlapping workout bookings with a daily limit. */
class TrainingCalendar {
  public:
    TrainingCalendar(const std::string &name = "Calendar", const std::vector<ScheduleSlot> &slots = {},
                     int daily_limit = 180);
    /** Read name. */
    const std::string &name() const { return name_; }
    /** Read slots. */
    const std::vector<ScheduleSlot> &slots() const { return slots_; }
    /** Read daily limit. */
    const int &daily_limit() const { return daily_limit_; }
    /** Book a workout after overlap and daily limit checks. */
    void book(const ScheduleSlot &slot);
    /** Sum booked workout minutes on a day. */
    int minutes_on(int day) const;
    /** Cancel all workout bookings for a day. */
    void cancel_day(int day);

  private:
    std::string name_;
    std::vector<ScheduleSlot> slots_;
    int daily_limit_;
};
} // namespace fitness
