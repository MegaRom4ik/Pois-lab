#pragma once
#include "HeartRateSample.hpp"
#include "SensorError.hpp"
#include "Support.hpp"
namespace fitness {
/** A user configured heart rate interval, without medical recommendations. */
class HeartRateZone {
  public:
    HeartRateZone(const std::string &name = "Custom", int minimum = 100, int maximum = 140);
    /** Read name. */
    const std::string &name() const { return name_; }
    /** Read minimum. */
    const int &minimum() const { return minimum_; }
    /** Read maximum. */
    const int &maximum() const { return maximum_; }
    /** Classify a reading into the configured inclusive zone. */
    bool contains(const HeartRateSample &sample) const;
    /** Count integer heart rates shared by two zones. */
    int overlap_width(const HeartRateZone &other) const;

  private:
    std::string name_;
    int minimum_;
    int maximum_;
};
} // namespace fitness
