#pragma once
#include "RecoveryError.hpp"
#include "SleepEntry.hpp"
#include "Support.hpp"
namespace fitness {
/** Daily sleep records and a user selected duration target. */
class SleepDiary {
  public:
    SleepDiary(const std::vector<SleepEntry> &entries = {}, int target_minutes = 480,
               const std::string &owner = "User");
    /** Read entries. */
    const std::vector<SleepEntry> &entries() const { return entries_; }
    /** Read target minutes. */
    const int &target_minutes() const { return target_minutes_; }
    /** Read owner. */
    const std::string &owner() const { return owner_; }
    /** Record a new daily sleep interval. */
    void record(const SleepEntry &entry);
    /** Calculate mean sleep duration in hours. */
    double average_hours() const;
    /** Sum shortfalls relative to the selected sleep duration. */
    int total_deficit() const;

  private:
    std::vector<SleepEntry> entries_;
    int target_minutes_;
    std::string owner_;
};
} // namespace fitness
