#include "HeartRateSeries.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw SensorError(message);
}
} // namespace
HeartRateSeries::HeartRateSeries(const std::vector<HeartRateSample> &samples, const std::string &label,
                                 int max_gap)
    : samples_(samples), label_(label), max_gap_(max_gap) {
    valid(!label_.empty() && max_gap_ > 0, "Invalid sensor series");
    auto initial = samples_;
    samples_.clear();
    for (const auto &sample : initial)
        append(sample);
}
void HeartRateSeries::append(const HeartRateSample &sample) {
    valid(samples_.empty() || sample.second() > samples_.back().second(), "Nonincreasing sample time");
    samples_.push_back(sample);
}
double HeartRateSeries::average() const {
    valid(!samples_.empty(), "No readings");
    double total = 0;
    for (const auto &sample : samples_)
        total += sample.bpm();
    return total / samples_.size();
}
int HeartRateSeries::seconds_in(const HeartRateZone &zone) const {
    int total = 0;
    for (std::size_t index = 1; index < samples_.size(); ++index) {
        const int gap = samples_[index].time_since(samples_[index - 1]);
        if (gap <= max_gap_ && zone.contains(samples_[index - 1])) total += gap;
    }
    return total;
}
} // namespace fitness
