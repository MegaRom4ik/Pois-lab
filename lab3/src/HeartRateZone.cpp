#include "HeartRateZone.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw SensorError(message);
}
} // namespace
HeartRateZone::HeartRateZone(const std::string &name, int minimum, int maximum)
    : name_(name), minimum_(minimum), maximum_(maximum) {
    valid(!name_.empty() && minimum_ > 0 && maximum_ >= minimum_, "Invalid zone");
}
bool HeartRateZone::contains(const HeartRateSample &sample) const {
    return sample.bpm() >= minimum_ && sample.bpm() <= maximum_;
}
int HeartRateZone::overlap_width(const HeartRateZone &other) const {
    return std::max(0, std::min(maximum_, other.maximum_) - std::max(minimum_, other.minimum_) + 1);
}
} // namespace fitness
