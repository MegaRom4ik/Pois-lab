#pragma once
#include "SensorError.hpp"
#include "Support.hpp"
namespace fitness {
/** A sensor reading at a relative timestamp. */
class HeartRateSample {
  public:
    HeartRateSample(int second = 0, int bpm = 100, const std::string &sensor = "manual");
    /** Read second. */
    const int &second() const { return second_; }
    /** Read bpm. */
    const int &bpm() const { return bpm_; }
    /** Read sensor. */
    const std::string &sensor() const { return sensor_; }
    /** Calculate time since an earlier sample. */
    int time_since(const HeartRateSample &previous) const;
    /** Calculate the change in beats per minute. */
    int change_from(const HeartRateSample &previous) const;

  private:
    int second_;
    int bpm_;
    std::string sensor_;
};
} // namespace fitness
