#pragma once
#include "ScheduleError.hpp"
#include "Support.hpp"
#include "Workout.hpp"
namespace fitness {
/** A workout scheduled within a single day. */
class ScheduleSlot {
  public:
    ScheduleSlot(int day = 0, int minute = 600, int duration_minutes = 60, const Workout &workout = {});
    /** Read day. */
    const int &day() const { return day_; }
    /** Read minute. */
    const int &minute() const { return minute_; }
    /** Read duration minutes. */
    const int &duration_minutes() const { return duration_minutes_; }
    /** Read workout. */
    const Workout &workout() const { return workout_; }
    /** Calculate the end time of a booking. */
    int end_minute() const;
    /** Detect overlapping bookings, excluding adjacent slots. */
    bool overlaps(const ScheduleSlot &other) const;

  private:
    int day_;
    int minute_;
    int duration_minutes_;
    Workout workout_;
};
} // namespace fitness
