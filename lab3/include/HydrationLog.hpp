#pragma once
#include "NutritionError.hpp"
#include "Support.hpp"
#include "WaterEntry.hpp"
namespace fitness {
/** Water servings and a user configured daily target. */
class HydrationLog {
  public:
    HydrationLog(const std::vector<WaterEntry> &entries = {}, double target_ml = 2000,
                 const std::string &owner = "User");
    /** Read entries. */
    const std::vector<WaterEntry> &entries() const { return entries_; }
    /** Read target ml. */
    const double &target_ml() const { return target_ml_; }
    /** Read owner. */
    const std::string &owner() const { return owner_; }
    /** Record an additional water serving. */
    void drink(const WaterEntry &entry);
    /** Sum water consumed on a day. */
    double total_on(int day) const;
    /** Calculate the remaining amount for the selected daily target. */
    double remaining_on(int day) const;

  private:
    std::vector<WaterEntry> entries_;
    double target_ml_;
    std::string owner_;
};
} // namespace fitness
