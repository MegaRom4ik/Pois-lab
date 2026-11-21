#pragma once
#include "HeartRateSample.hpp"
#include "HeartRateZone.hpp"
#include "SensorError.hpp"
#include "Support.hpp"
namespace fitness {
/** Ordered readings with a maximum interval for time integration. */
class HeartRateSeries {
  public:
    HeartRateSeries(const std::vector<HeartRateSample> &samples = {}, const std::string &label = "Session",
                    int max_gap = 60);
    /** Read samples. */
    const std::vector<HeartRateSample> &samples() const { return samples_; }
    /** Read label. */
    const std::string &label() const { return label_; }
    /** Read max gap. */
    const int &max_gap() const { return max_gap_; }
    /** Append a reading at a strictly later time. */
    void append(const HeartRateSample &sample);
    /** Calculate the arithmetic mean of recorded readings. */
    double average() const;
    /** Integrate left endpoint readings while excluding long sensor gaps. */
    int seconds_in(const HeartRateZone &zone) const;

  private:
    std::vector<HeartRateSample> samples_;
    std::string label_;
    int max_gap_;
};
} // namespace fitness
