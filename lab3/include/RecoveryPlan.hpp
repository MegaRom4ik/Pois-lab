#pragma once
#include "RecoveryError.hpp"
#include "Support.hpp"
#include "TrainingCalendar.hpp"
namespace fitness {
/** A rest-day policy based on the recorded calendar. */
class RecoveryPlan {
  public:
    RecoveryPlan(const std::string &name = "Recovery", int minimum_rest_days = 2, int first_day = 0);
    /** Read name. */
    const std::string &name() const { return name_; }
    /** Read minimum rest days. */
    const int &minimum_rest_days() const { return minimum_rest_days_; }
    /** Read first day. */
    const int &first_day() const { return first_day_; }
    /** Count unbooked days in a seven day schedule. */
    int rest_days(const TrainingCalendar &calendar) const;
    /** Check the user configured minimum number of rest days. */
    bool respected(const TrainingCalendar &calendar) const;

  private:
    std::string name_;
    int minimum_rest_days_;
    int first_day_;
};
} // namespace fitness
