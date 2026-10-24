#include "Distance.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw DistanceError(message);
}
} // namespace
Distance::Distance(double meters, double ascent, const std::string &surface)
    : meters_(meters), ascent_(ascent), surface_(surface) {
    valid(meters_ >= 0 && ascent_ >= 0 && std::isfinite(meters_) && std::isfinite(ascent_),
          "Invalid distance");
}
double Distance::kilometers() const { return meters_ / 1000.0; }
double Distance::grade() const {
    valid(meters_ > 0, "Zero route length");
    return ascent_ / meters_;
}
Distance Distance::joined(const Distance &other) const {
    return Distance(meters_ + other.meters_, ascent_ + other.ascent_, surface_);
}
} // namespace fitness
