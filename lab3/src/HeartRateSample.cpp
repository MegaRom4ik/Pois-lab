#include "HeartRateSample.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw SensorError(message);
}
} // namespace
HeartRateSample::HeartRateSample(int second, int bpm, const std::string &sensor)
    : second_(second), bpm_(bpm), sensor_(sensor) {
    valid(second_ >= 0 && bpm_ > 0 && !sensor_.empty(), "Invalid heart rate reading");
}
int HeartRateSample::time_since(const HeartRateSample &previous) const {
    valid(second_ >= previous.second_, "Reading predates previous");
    return second_ - previous.second_;
}
int HeartRateSample::change_from(const HeartRateSample &previous) const { return bpm_ - previous.bpm_; }
} // namespace fitness
