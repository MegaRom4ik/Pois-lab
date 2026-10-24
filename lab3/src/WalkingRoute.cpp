#include "WalkingRoute.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw DistanceError(message);
}
} // namespace
WalkingRoute::WalkingRoute(const std::string &name, const std::vector<Distance> &segments, bool loop)
    : name_(name), segments_(segments), loop_(loop) {
    valid(!name_.empty(), "Empty route name");
}
void WalkingRoute::extend(const Distance &segment) { segments_.push_back(segment); }
Distance WalkingRoute::total_distance() const {
    Distance total(0);
    for (const auto &segment : segments_)
        total = total.joined(segment);
    return total;
}
double WalkingRoute::round_trip_meters() const { return total_distance().meters() * (loop_ ? 1 : 2); }
} // namespace fitness
