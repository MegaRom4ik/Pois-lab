#include "Lap.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw DistanceError(message);
}
} // namespace
Lap::Lap(int number, const Distance &distance, const Duration &duration)
    : number_(number), distance_(distance), duration_(duration) {
    valid(number_ > 0 && distance_.meters() > 0, "Invalid lap");
}
double Lap::seconds_per_100m() const { return duration_.active() / distance_.meters() * 100.0; }
double Lap::time_difference(const Lap &other) const {
    valid(distance_.meters() == other.distance_.meters(), "Different lap distances");
    return duration_.active() - other.duration_.active();
}
} // namespace fitness
